find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(ExampleStreamerTests test_data_streamer.cpp)
target_link_libraries(ExampleStreamerTests
    PRIVATE
    example-streamer
    GTest::gtest
    GTest::gtest_main
)
gtest_discover_tests(ExampleStreamerTests)
