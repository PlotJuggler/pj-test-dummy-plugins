cmake_minimum_required(VERSION 3.15)
project(CanBusParser VERSION 1.0.0 LANGUAGES CXX)

set(PLUGIN_NAME "can-bus-parser")
set(PLUGIN_VERSION "1.0.0")

set(SOURCES src/CanBusParser.cpp src/PluginEntry.cpp)
set(HEADERS include/CanBusParser.h)

add_library(${PLUGIN_NAME} SHARED ${SOURCES} ${HEADERS})
target_include_directories(${PLUGIN_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
set_target_properties(${PLUGIN_NAME} PROPERTIES
    VERSION ${PLUGIN_VERSION} SOVERSION 1 OUTPUT_NAME ${PLUGIN_NAME} PREFIX ""
)
install(TARGETS ${PLUGIN_NAME} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)
install(FILES ${HEADERS} DESTINATION include/${PLUGIN_NAME})

if(BUILD_TESTS)
    add_subdirectory(test)
endif()
