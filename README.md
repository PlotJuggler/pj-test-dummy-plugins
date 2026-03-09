# pj-test-dummy-plugins

Three example C++ plugins (shared libraries) with a complete CI/CD pipeline using **pixi** + **conan 2.0**, and GitHub Actions workflows for Ubuntu (x86_64 + aarch64), Windows (x64 + arm64), and macOS (x86_64 + arm64).

## Plugins

| Plugin | Description |
|---|---|
| `example-streamer` | DataStreamer shared library — streams data from a source |
| `custom-toolbox` | Toolbox shared library — string formatting, hashing, validation and transforms |
| `example-data-loader` | DataLoader shared library — loads and processes data from various sources |

Each plugin has its own GTest suite (19 tests total).

## Requirements

- [pixi](https://pixi.sh) — manages the toolchain (cmake, ninja, conan, ccache, gcc/clang)
- [Docker](https://docs.docker.com/get-docker/) — required for local CI testing with `act`
- [act](https://github.com/nektos/act) *(optional)* — run GitHub Actions workflows locally

## Build locally

```bash
pixi run all      # conan install → cmake configure → build → ctest
pixi run clean    # remove build/
```

## Test CI locally with act

```bash
# Ubuntu x86_64
act push -W .github/workflows/ubuntu.yml --matrix ubuntu-runner:ubuntu-22.04

# Ubuntu aarch64 (requires QEMU)
act push -W .github/workflows/ubuntu.yml --matrix ubuntu-runner:ubuntu-22.04-arm

# Windows x64 (runs in a Linux container)
act push -W .github/workflows/windows.yml --matrix arch:x64

# macOS x86_64 (runs in a Linux container)
act push -W .github/workflows/macos.yml --matrix arch:x86_64

# Simulate a release tag
act push -W .github/workflows/ubuntu.yml --eventpath test-event-tag.json
```

> **Note:** Windows arm64 and macOS arm64 jobs require real runners and cannot be fully validated with `act`.

## Release

A GitHub Release is created automatically when a version tag is pushed:

```bash
git tag 1.0.0
git push origin 1.0.0
```

The release includes these artifacts:

```
pj-test-dummy-plugins-1.0.0-linux-x86_64.tar.gz
pj-test-dummy-plugins-1.0.0-linux-aarch64.tar.gz
pj-test-dummy-plugins-1.0.0-windows-x64.zip
pj-test-dummy-plugins-1.0.0-windows-arm64.zip
pj-test-dummy-plugins-1.0.0-macos-x86_64.tar.gz
pj-test-dummy-plugins-1.0.0-macos-arm64.tar.gz
```

## Project structure

```
pj-test-dummy-plugins/
├── CMakeLists.txt                   # root, includes the 3 plugins
├── conanfile.py                     # C++ dependency: gtest/1.14.0
├── pixi.toml                        # toolchain + tasks (linux, windows, macos)
├── pixi.lock                        # locked environment for linux platforms
├── .actrc                           # runner mapping for local act testing
├── .github/workflows/
│   ├── ubuntu.yml                   # matrix: ubuntu-22.04 (x86_64) + ubuntu-22.04-arm (aarch64)
│   ├── windows.yml                  # matrix: windows-latest (x64) + windows-11-arm (arm64)
│   └── macos.yml                    # matrix: macos-13 (x86_64) + macos-14 (arm64)
└── plugins/
    ├── example-streamer/            # DataStreamer plugin + GTest suite
    ├── custom-toolbox/              # Toolbox plugin + GTest suite
    └── example-data-loader/         # DataLoader plugin + GTest suite
```
