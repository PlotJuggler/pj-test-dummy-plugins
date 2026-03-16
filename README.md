# pj-test-dummy-plugins

> **Note:** This repository is a work in progress and is used internally for testing the PlotJuggler Marketplace infrastructure.

Six dummy C++ extensions (shared libraries) for the PlotJuggler Marketplace POC, with a complete CI/CD pipeline using **conan 2.0** and GitHub Actions workflows for Ubuntu (x86_64 + aarch64), Windows (x64 + arm64), and macOS (x86_64 + arm64).

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

- Python + pip
- A C++ compiler: gcc/g++ on Linux, clang on macOS, MSVC on Windows

## Build locally

```bash
pip install cmake "conan>=2.0,<3"
conan profile detect --force
conan install . --output-folder=build --build=missing -s build_type=Release
cmake -S . -B build/Release -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON
cmake --build build/Release --config Release
ctest --test-dir build/Release -V --output-on-failure
```

---

## Release

Releases are **per extension** following the mono-repo strategy in `plotjuggler-marketplace-spec-v1.0.0` §9.

### Bumping version

When releasing a new version, update the version string in **4 places**:

1. `extensions/<name>/manifest.json` — the `"version"` field
2. `extensions/<name>/src/PluginEntry.cpp` — the `"version"` in `getMetadata()`
3. `extensions/<name>/src/<Name>.cpp` — the `getVersion()` return value
4. `extensions/<name>/test/test_<name>.cpp` — the version assertion in `GetVersion` test

### Creating a release tag

After merging the version bump to `development`, create and push the tag:

```bash
git checkout development
git pull origin development
git tag csv-loader/v1.0.0
git push origin csv-loader/v1.0.0
```

The unified workflow runs all 6 matrix jobs in parallel (linux x86_64, linux aarch64, macos x86_64, macos arm64, windows x64, windows arm64). Each builds the full project but packages **only the tagged extension**. The six resulting zips are attached to a single GitHub Release:

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
├── .github/workflows/
│   └── build.yml                    # unified matrix: 6 jobs (linux x86_64/aarch64, macos x86_64/arm64, windows x64/arm64)
└── extensions/
    ├── csv-loader/                  # CsvLoader extension + GTest suite
    ├── ros2-streaming/              # Ros2Streaming extension + GTest suite
    ├── mcap-loader/                 # McapLoader extension + GTest suite
    ├── fft-toolbox/                 # FftToolbox extension + GTest suite
    ├── can-bus-parser/              # CanBusParser extension + GTest suite
    └── ros-bundle/                  # RosBundle extension + GTest suite
```
