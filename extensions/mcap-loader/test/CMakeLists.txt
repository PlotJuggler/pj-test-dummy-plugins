find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(McapLoaderTests test_mcap_loader.cpp)
target_link_libraries(McapLoaderTests PRIVATE mcap-loader GTest::gtest GTest::gtest_main)
gtest_discover_tests(McapLoaderTests)
