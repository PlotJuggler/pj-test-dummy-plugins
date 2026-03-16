cmake_minimum_required(VERSION 3.25)
project(plotjuggler-plugins VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# On Windows/MSVC, shared libraries need __declspec(dllexport) to generate an
# import library (.lib). Since plugins use Linux-style exports, enable auto-export
# so MSVC produces the .lib needed by test executables.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# On Windows, DLLs and test executables must be in the same directory so the
# runtime loader can find them. Centralise all runtime outputs.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(GTest REQUIRED)
include(GoogleTest)
include(CTest)
enable_testing()

option(BUILD_TESTS "Build plugin tests" ON)

add_subdirectory(extensions/csv-loader)
add_subdirectory(extensions/ros2-streaming)
add_subdirectory(extensions/mcap-loader)
add_subdirectory(extensions/fft-toolbox)
add_subdirectory(extensions/can-bus-parser)
add_subdirectory(extensions/ros-bundle)
