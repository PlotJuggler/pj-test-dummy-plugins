find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(RosBundleTests test_ros_bundle.cpp)
target_link_libraries(RosBundleTests PRIVATE ros-bundle GTest::gtest GTest::gtest_main)
gtest_discover_tests(RosBundleTests)
