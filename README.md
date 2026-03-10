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
extern "C" const char* getMetadata();
```

> **Resolved:** function name is `getMetadata()` per PLAN.md §4 (Week 1). ARCHITECTURE.md §7.2 previously listed `getPluginMetadata()` — this has been aligned.

---

## ZIP artifact structure

Releases are **per extension**. Each zip contains one subdirectory ready to be extracted into `~/.plotjuggler/extensions/` (see [ARCHITECTURE.md §5.1](../plotjuggler_core/pj_marketplace/documentation/ARCHITECTURE.md)):

```
csv-loader-1.0.0-linux-x86_64.zip
└── csv-loader/
    ├── csv-loader.so
    └── manifest.json
```

Six zips are produced per release tag (one per platform/arch combination).

---

## Requirements

- [pixi](https://pixi.sh) — manages the toolchain (cmake, ninja, conan, ccache, gcc/clang)

## Build locally

```bash
pixi run all      # conan install → cmake configure → build → ctest
pixi run clean    # remove build/
```

---

## Release

Releases are **per extension** following the mono-repo strategy in `plotjuggler-marketplace-spec-v1.0.0` §9. Push a tag with the format `<extension>/v<version>`:

```bash
git tag csv-loader/v1.0.0
git push origin csv-loader/v1.0.0
```

All three workflows (ubuntu, macos, windows) run in parallel. Each builds the full project but packages **only the tagged extension**. The six resulting zips are attached to a single GitHub Release:

```
csv-loader-1.0.0-linux-x86_64.zip
csv-loader-1.0.0-linux-aarch64.zip
csv-loader-1.0.0-macos-x86_64.zip
csv-loader-1.0.0-macos-arm64.zip
csv-loader-1.0.0-windows-x64.zip
csv-loader-1.0.0-windows-arm64.zip
```

---

## Project structure

```
pj-test-dummy-plugins/
├── CMakeLists.txt                   # root, includes all 6 extensions
├── conanfile.py                     # C++ dependency: gtest/1.14.0
├── pixi.toml                        # toolchain + tasks (linux, windows, macos)
├── pixi.lock                        # locked environment for linux platforms
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
