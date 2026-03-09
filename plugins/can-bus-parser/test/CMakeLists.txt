find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(CanBusParserTests test_can_bus_parser.cpp)
target_link_libraries(CanBusParserTests PRIVATE can-bus-parser GTest::gtest GTest::gtest_main)
gtest_discover_tests(CanBusParserTests)
