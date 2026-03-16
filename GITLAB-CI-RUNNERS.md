# GitLab CI — Runners & Pipeline Design Notes

This document explains the runner setup used in `.gitlab-ci.yml` and the reasons behind
specific implementation choices, to avoid confusion when maintaining or extending the pipeline.

---

## Runners

### Runner #33 — CocoSet (`self-hosted`, `linux`, `amd64`)

- **Executor:** Shell
- **OS:** Linux x86_64
- **Docker:** Available (used as a build tool, not as the executor)

This runner uses a **shell executor**, meaning GitLab Runner executes commands directly in
a shell on the host machine. There is no `image:` directive in the jobs that use this runner
— if you add one, it will be silently ignored.

Because Docker is available on the host, the Linux build jobs use it as a build tool:
they build a Docker image containing the full toolchain, compile the project inside it,
then extract the compiled artifacts using `docker cp`. This pattern isolates the build
environment without requiring a Docker executor.

```
docker build → docker create → docker cp → docker rm
```

### Runner #26 — PCRiskooPortatil (`win64`)

- **Executor:** Shell (PowerShell)
- **OS:** Windows x64
- **Tools pre-installed:** Python 3.12, conan 2.x, Visual Studio 2022 (MSVC 194)

This runner also uses a shell executor. The `build-windows-x64` job runs PowerShell
commands directly on the machine.

---

## Why certain things are configured the way they are

### `$ErrorActionPreference = "Stop"` (Windows job)

PowerShell does **not** stop on errors by default. Without this setting, if `cmake` or
`ctest` fails, PowerShell prints the error and continues to the next command. The job
then exits with code 0 (success) even though the build failed. Setting
`$ErrorActionPreference = "Stop"` makes the job fail immediately when any command errors.

### cmake PATH on Windows (vswhere)

cmake is bundled with Visual Studio 2022 but is **not** added to the system PATH. The
GitLab Runner service runs under a different user (SYSTEM), so user-level PATH entries
don't apply. The fix is to locate the Visual Studio install path at runtime using
`vswhere.exe` and prepend the bundled cmake binary directory to `$env:PATH`:

```powershell
$vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
$vsInstallPath = & $vswhere -latest -property installationPath
$cmakePath = "$vsInstallPath\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin"
$env:PATH = "$cmakePath;$env:PATH"
```

This is more robust than hardcoding a path, as it works across VS editions (Community,
Professional, Enterprise) and different install locations.

### `cmake_minimum_required(VERSION 3.22)` in CMakeLists.txt

Ubuntu 22.04 ships cmake **3.22.1** via apt. The Docker images for both Linux builds
(`docker/linux-x86_64/Dockerfile.build` and `docker/linux-aarch64/Dockerfile.build`)
install cmake from apt, so requiring 3.25+ would make the Docker builds fail. Nothing in
this project requires cmake features beyond 3.22. The GitHub Actions workflow uses pixi,
which installs a newer cmake independently and is not affected by this constraint.

### Linux aarch64 on an amd64 runner (QEMU + docker buildx)

Runner #33 is an x86_64 machine. To produce an ARM64 shared library without a dedicated
ARM runner, the pipeline uses QEMU emulation:

```yaml
- docker run --rm --privileged multiarch/qemu-user-static --reset -p yes
- docker buildx build --platform linux/arm64 --load -t ... -f docker/linux-aarch64/Dockerfile.build .
```

The first command registers QEMU binfmt handlers in the kernel so the host can
transparently execute ARM64 binaries. The second command builds a proper `linux/arm64`
Docker image, which runs the ARM64 toolchain inside QEMU. The base image
(`arm64v8/ubuntu:22.04`) is a native ARM64 image — all binaries compiled inside it are
ARM64 ELF.

### Release job uses curl, not `release-cli`

The standard GitLab approach for creating releases uses a job with `image: registry.gitlab.com/gitlab-org/release-cli`.
However, since Runner #33 is a shell executor, the `image:` directive is ignored and
`release-cli` is not available. The release job instead calls the GitLab Releases REST
API directly via `curl`:

```bash
curl --fail --request POST \
     --header "JOB-TOKEN: ${CI_JOB_TOKEN}" \
     --header "Content-Type: application/json" \
     --data "{ ... }" \
     "${CI_API_V4_URL}/projects/${CI_PROJECT_ID}/releases"
```

This produces the same result as `release-cli` with no additional tooling required.

### When pipelines are triggered (`workflow: rules`)

```yaml
workflow:
  rules:
    - if: $CI_COMMIT_TAG
    - if: $CI_PIPELINE_SOURCE == "merge_request_event"
    - if: $CI_COMMIT_BRANCH
```

| Event | Pipeline created | Jobs that run |
|---|---|---|
| Push to a branch (no open MR) | Yes | build × 3 |
| MR opened or updated | Yes | build × 3 |
| Push to a branch with an open MR | **No** (branch pipeline skipped) | MR pipeline runs instead |
| Tag pushed (`git tag 1.0.0`) | Yes | build × 3 + release |

The third case avoids duplicate pipelines: when a branch already has an open MR, the
branch push does not create a redundant pipeline — only the MR pipeline runs.

### Releases are only created on explicit version tags

The `release` job has:

```yaml
rules:
  - if: $CI_COMMIT_TAG
```

It will never run on a branch push or MR. A release is an intentional act:

```bash
git tag 1.0.0
git push origin 1.0.0
```

This pushes the tag, triggers the full pipeline (build × 3 + release), uploads the zips
to the Package Registry permanently, and creates a GitLab Release with download links.
Temporary test tags (e.g. `1.0.0-test`) can be deleted afterwards:

```bash
git push origin --delete 1.0.0-test
git tag --delete 1.0.0-test
```

### `optional: true` for aarch64 and Windows in the release job

```yaml
needs:
  - job: build-linux-x86_64
    optional: false
  - job: build-linux-aarch64
    optional: true
  - job: build-windows-x64
    optional: true
```

The release is created even if the aarch64 or Windows builds failed, as long as the
x86_64 build succeeded. This avoids blocking a release over a platform-specific failure.

---

## Artifact and Package Registry flow

```
branch push  →  build jobs run  →  .zip uploaded as GitLab CI artifact (expires in 1 week)
tag push     →  build jobs run  →  .zip uploaded to Package Registry (permanent)
                                →  release job creates a GitLab Release with download links
```

Package Registry URL pattern:
```
{CI_API_V4_URL}/projects/{CI_PROJECT_ID}/packages/generic/pj-test-dummy-plugins/{tag}/{filename}
```
