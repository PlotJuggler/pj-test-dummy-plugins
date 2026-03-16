cmake_minimum_required(VERSION 3.22)
project(plotjuggler-plugins VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
