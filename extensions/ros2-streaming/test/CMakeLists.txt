find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(Ros2StreamingTests test_ros2_streaming.cpp)
target_link_libraries(Ros2StreamingTests PRIVATE ros2-streaming GTest::gtest GTest::gtest_main)
gtest_discover_tests(Ros2StreamingTests)
