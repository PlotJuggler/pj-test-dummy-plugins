#include "RosBundle.h"

extern "C" {

PluginSystem::RosBundle* createRosBundle() {
    return new PluginSystem::RosBundle();
}

const char* getMetadata() {
    return R"({
        "id": "ros-bundle",
        "name": "ROS Bundle",
        "version": "1.0.0",
        "description": "Meta-extension that groups ROS-related plugins and reports availability",
        "category": "toolbox",
        "min_plotjuggler_version": "4.0.0"
    })";
}

}
