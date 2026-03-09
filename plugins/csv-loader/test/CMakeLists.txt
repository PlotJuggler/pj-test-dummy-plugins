find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(CsvLoaderTests test_csv_loader.cpp)
target_link_libraries(CsvLoaderTests PRIVATE csv-loader GTest::gtest GTest::gtest_main)
gtest_discover_tests(CsvLoaderTests)
