#include "McapLoader.h"

extern "C" PluginSystem::McapLoader* createMcapLoader() {
    return new PluginSystem::McapLoader();
}
