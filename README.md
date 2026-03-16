# pj-test-dummy-plugins

Six dummy C++ extensions (shared libraries) for the PlotJuggler Marketplace POC, with a complete CI/CD pipeline using **pixi** + **conan 2.0** and GitHub Actions workflows for Ubuntu (x86_64 + aarch64), Windows (x64 + arm64), and macOS (x86_64 + arm64).

This repository covers the **dummy extensions** deliverable of **Week 1** of the PlotJuggler Marketplace implementation plan (5–11 March 2026). See [ARCHITECTURE.md §7.2](../plotjuggler_core/pj_marketplace/documentation/ARCHITECTURE.md) and [PLAN.md §4](../plotjuggler_core/pj_marketplace/documentation/PLAN.md) for full context.

All extensions are implemented under the `PluginSystem` namespace with no external dependencies beyond the standard library.

---

## Extensions

| Extension | Class | Category | Description |
|---|---|---|---|
| `csv-loader` | `CsvLoader` | data_loader | Loads CSV files and exposes column names |
| `ros2-streaming` | `Ros2Streaming` | data_streamer | Connects to a ROS 2 host and lists available topics |
| `mcap-loader` | `McapLoader` | data_loader | Opens MCAP files and lists available channels |
| `fft-toolbox` | `FftToolbox` | toolbox | Computes FFT over sample vectors with configurable window functions |
| `can-bus-parser` | `CanBusParser` | parser | Loads a DBC file and parses CAN frames into signal maps |
| `ros-bundle` | `RosBundle` | toolbox | Meta-extension that groups ROS-related plugins and reports availability |

28 GTest unit tests total (across all 6 extensions).

---

## Extension structure

Each extension follows the structure defined in [ARCHITECTURE.md §5.2](../plotjuggler_core/pj_marketplace/documentation/ARCHITECTURE.md):

```
extensions/<name>/
├── include/          # Public header
├── src/
│   ├── <Name>.cpp    # Implementation
│   └── PluginEntry.cpp  # Exported C functions
├── test/             # GTest suite
├── CMakeLists.txt
└── manifest.json     # Extension metadata (id, name, version, category...)
```

### Exported C functions (per ARCHITECTURE.md §7.2)

Each compiled shared library exposes two `extern "C"` functions:

```cpp
// Factory — creates the plugin instance
extern "C" PluginSystem::<Name>* create<Name>();

// Metadata — returns a JSON string with extension info
extern "C" const char* getPluginMetadata();
```

> **Open question:** PLAN.md §4 (Week 1) names the function `getMetadata()`, while ARCHITECTURE.md §7.2 names it `getPluginMetadata()`. Currently implemented as `getPluginMetadata()` following the architecture. **Needs alignment.**

---

## ZIP artifact structure

Each release zip contains one subdirectory per extension, ready to be extracted directly into `~/.plotjuggler/extensions/` (see [ARCHITECTURE.md §5.1](../plotjuggler_core/pj_marketplace/documentation/ARCHITECTURE.md)):

```
pj-test-dummy-plugins-1.0.0-linux-x86_64.zip
├── csv-loader/
│   ├── csv-loader.so
│   └── manifest.json
├── ros2-streaming/
│   ├── ros2-streaming.so
│   └── manifest.json
└── ... (6 extensions total)
```

---

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

---

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

---

## Project structure

```
pj-test-dummy-plugins/
├── CMakeLists.txt                   # root, includes all 6 extensions
├── conanfile.py                     # C++ dependency: gtest/1.14.0
├── pixi.toml                        # toolchain + tasks (linux, windows, macos)
├── pixi.lock                        # locked environment for linux platforms
├── test-event-tag.json              # event file for simulating tag push with act
├── .actrc                           # runner mapping for local act testing
├── docker/
│   ├── linux-x86_64/Dockerfile.build   # builds x86_64 inside Docker (GitLab CI)
│   └── linux-aarch64/Dockerfile.build  # builds aarch64 via buildx + QEMU (GitLab CI)
├── .github/workflows/
│   ├── ubuntu.yml                   # matrix: ubuntu-22.04 (x86_64) + ubuntu-22.04-arm (aarch64)
│   ├── windows.yml                  # matrix: windows-latest (x64) + windows-11-arm (arm64)
│   └── macos.yml                    # matrix: macos-13 (x86_64) + macos-14 (arm64)
└── extensions/
    ├── csv-loader/                  # CsvLoader extension + GTest suite
    ├── ros2-streaming/              # Ros2Streaming extension + GTest suite
    ├── mcap-loader/                 # McapLoader extension + GTest suite
    ├── fft-toolbox/                 # FftToolbox extension + GTest suite
    ├── can-bus-parser/              # CanBusParser extension + GTest suite
    └── ros-bundle/                  # RosBundle extension + GTest suite
```
