#include "Ros2Streaming.h"

extern "C" PluginSystem::Ros2Streaming* createRos2Streaming() {
    return new PluginSystem::Ros2Streaming();
}
