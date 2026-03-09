cmake_minimum_required(VERSION 3.25)
project(plotjuggler-plugins VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include(GoogleTest)
include(CTest)
enable_testing()

option(BUILD_TESTS "Build plugin tests" ON)

add_subdirectory(plugins/csv-loader)
add_subdirectory(plugins/ros2-streaming)
add_subdirectory(plugins/mcap-loader)
add_subdirectory(plugins/fft-toolbox)
add_subdirectory(plugins/can-bus-parser)
add_subdirectory(plugins/ros-bundle)
