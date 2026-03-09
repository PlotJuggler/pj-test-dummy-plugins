cmake_minimum_required(VERSION 3.25)
project(plotjuggler-plugins VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include(GoogleTest)
include(CTest)
enable_testing()

option(BUILD_TESTS "Build plugin tests" ON)

add_subdirectory(plugins/example-streamer)
add_subdirectory(plugins/custom-toolbox)
add_subdirectory(plugins/example-data-loader)
