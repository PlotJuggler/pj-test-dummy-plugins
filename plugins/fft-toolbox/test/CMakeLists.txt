find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(FftToolboxTests test_fft_toolbox.cpp)
target_link_libraries(FftToolboxTests PRIVATE fft-toolbox GTest::gtest GTest::gtest_main)
gtest_discover_tests(FftToolboxTests)
