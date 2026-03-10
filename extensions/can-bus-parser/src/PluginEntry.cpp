#include "CanBusParser.h"

extern "C" {

PluginSystem::CanBusParser* createCanBusParser() {
    return new PluginSystem::CanBusParser();
}

const char* getMetadata() {
    return R"({
        "id": "can-bus-parser",
        "name": "CAN Bus Parser",
        "version": "1.0.0",
        "description": "Loads a DBC file and parses CAN frames into signal maps",
        "category": "parser",
        "min_plotjuggler_version": "4.0.0"
    })";
}

}
