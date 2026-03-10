#include "Ros2Streaming.h"

extern "C" {

PluginSystem::Ros2Streaming* createRos2Streaming() {
    return new PluginSystem::Ros2Streaming();
}

const char* getMetadata() {
    return R"({
        "id": "ros2-streaming",
        "name": "ROS 2 Streaming",
        "version": "1.0.0",
        "description": "Connects to a ROS 2 host and lists available topics",
        "category": "data_streamer",
        "min_plotjuggler_version": "4.0.0"
    })";
}

}
