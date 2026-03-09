#include "DataLoader.h"

extern "C" PLUGIN_EXPORT PluginSystem::PluginInterface* createPlugin() {
    return new PluginSystem::DataLoader();
}
