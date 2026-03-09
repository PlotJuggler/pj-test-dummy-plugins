find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(ExampleDataLoaderTests test_data_loader.cpp)
target_link_libraries(ExampleDataLoaderTests
    PRIVATE
    example-data-loader
    GTest::gtest
    GTest::gtest_main
)
gtest_discover_tests(ExampleDataLoaderTests)
