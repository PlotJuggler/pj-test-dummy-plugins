#include "RosBundle.h"

extern "C" PluginSystem::RosBundle* createRosBundle() {
    return new PluginSystem::RosBundle();
}
