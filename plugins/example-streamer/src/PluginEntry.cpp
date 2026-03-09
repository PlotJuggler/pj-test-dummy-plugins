#include "DataStreamer.h"

extern "C" PluginSystem::DataStreamer* createDataStreamer() {
    return new PluginSystem::DataStreamer();
}
