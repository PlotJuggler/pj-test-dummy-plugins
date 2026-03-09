find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(CustomToolboxTests test_toolbox.cpp)
target_link_libraries(CustomToolboxTests
    PRIVATE
    custom-toolbox
    GTest::gtest
    GTest::gtest_main
)
gtest_discover_tests(CustomToolboxTests)
