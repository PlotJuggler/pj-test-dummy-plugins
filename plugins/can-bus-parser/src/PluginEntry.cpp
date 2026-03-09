#include "CanBusParser.h"

extern "C" PluginSystem::CanBusParser* createCanBusParser() {
    return new PluginSystem::CanBusParser();
}
