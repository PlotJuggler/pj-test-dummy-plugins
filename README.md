# pj-test-dummy-plugins

Six example C++ plugins (shared libraries) representing a PlotJuggler-compatible marketplace, with a complete CI/CD pipeline using **pixi** + **conan 2.0** and GitHub Actions workflows for Ubuntu (x86_64 + aarch64), Windows (x64 + arm64), and macOS (x86_64 + arm64).

All plugins are implemented under the `PluginSystem` namespace with no external dependencies beyond the standard library.

## Plugins

| Plugin | Class | Description |
|---|---|---|
| `csv-loader` | `CsvLoader` | Loads CSV files and exposes column names |
| `ros2-streaming` | `Ros2Streaming` | Connects to a ROS 2 host and lists available topics |
| `mcap-loader` | `McapLoader` | Opens MCAP files and lists available channels |
| `fft-toolbox` | `FftToolbox` | Computes FFT over sample vectors with configurable window functions |
| `can-bus-parser` | `CanBusParser` | Loads a DBC file and parses CAN frames into signal maps |
| `ros-bundle` | `RosBundle` | Meta-plugin that groups ROS-related plugins and reports availability |

28 GTest unit tests total (across all 6 plugins).

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

# Windows x64 (runs in a Linux container via act)
act push -W .github/workflows/windows.yml --matrix arch:x64

# macOS x86_64 (runs in a Linux container via act)
act push -W .github/workflows/macos.yml --matrix arch:x86_64

# Simulate a release tag (verifies artifact packaging)
act push -W .github/workflows/ubuntu.yml \
  --eventpath test-event-tag.json \
  --matrix ubuntu-runner:ubuntu-22.04 \
  --artifact-server-path /tmp/act-artifacts
```

> **Note:** Windows arm64 and macOS arm64 jobs require real GitHub-hosted runners and cannot be fully validated with `act` locally.

> **Note:** The `Upload artifact` step will fail in act (no `ACTIONS_RUNTIME_TOKEN`). This is expected — the build and packaging steps succeed correctly. On real GitHub runners the full flow works.

## Release

A GitHub Release is created automatically when a version tag is pushed:

```bash
git tag 1.0.0
git push origin 1.0.0
```

All three workflows (ubuntu, macos, windows) run in parallel and each uploads its artifacts to the same release. The release is created by the ubuntu workflow (which also auto-generates release notes from commits since the previous tag). macOS and Windows attach their zips without modifying the description.

The release includes these artifacts:

```
pj-test-dummy-plugins-1.0.0-linux-x86_64.zip
pj-test-dummy-plugins-1.0.0-linux-aarch64.zip
pj-test-dummy-plugins-1.0.0-macos-x86_64.zip
pj-test-dummy-plugins-1.0.0-macos-arm64.zip
pj-test-dummy-plugins-1.0.0-windows-x64.zip
pj-test-dummy-plugins-1.0.0-windows-arm64.zip
```

Each zip contains the compiled shared libraries for that platform (`.so` on Linux, `.dylib` on macOS, `.dll` on Windows).

## Project structure

```
pj-test-dummy-plugins/
├── CMakeLists.txt                   # root, includes all 6 plugins
├── conanfile.py                     # C++ dependency: gtest/1.14.0
├── pixi.toml                        # toolchain + tasks (linux, windows, macos)
├── pixi.lock                        # locked environment for linux platforms
├── test-event-tag.json              # event file for simulating tag push with act
├── .actrc                           # runner mapping for local act testing
├── .github/workflows/
│   ├── ubuntu.yml                   # matrix: ubuntu-22.04 (x86_64) + ubuntu-22.04-arm (aarch64)
│   ├── windows.yml                  # matrix: windows-latest (x64) + windows-11-arm (arm64)
│   └── macos.yml                    # matrix: macos-13 (x86_64) + macos-14 (arm64)
└── plugins/
    ├── csv-loader/                  # CsvLoader plugin + GTest suite
    ├── ros2-streaming/              # Ros2Streaming plugin + GTest suite
    ├── mcap-loader/                 # McapLoader plugin + GTest suite
    ├── fft-toolbox/                 # FftToolbox plugin + GTest suite
    ├── can-bus-parser/              # CanBusParser plugin + GTest suite
    └── ros-bundle/                  # RosBundle plugin + GTest suite
```
