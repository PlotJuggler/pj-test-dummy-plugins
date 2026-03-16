#include "McapLoader.h"

extern "C" {

PluginSystem::McapLoader* createMcapLoader() {
    return new PluginSystem::McapLoader();
}

const char* getPluginMetadata() {
    return R"({
        "id": "mcap-loader",
        "name": "MCAP Loader",
        "version": "1.0.0",
        "description": "Opens MCAP files and lists available channels",
        "category": "data_loader",
        "min_plotjuggler_version": "4.0.0"
    })";
}

}
