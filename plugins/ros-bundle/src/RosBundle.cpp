#include "RosBundle.h"
#include <algorithm>

namespace PluginSystem {

RosBundle::RosBundle() {}
RosBundle::~RosBundle() {}
std::string RosBundle::getName() const { return "ROS Bundle"; }
std::string RosBundle::getVersion() const { return "1.0.0"; }

std::vector<std::string> RosBundle::getIncludedPlugins() const {
    return {"ros1-bag-loader", "ros2-streaming", "rosbridge"};
}

bool RosBundle::isAvailable(const std::string& pluginName) const {
    auto plugins = getIncludedPlugins();
    return std::find(plugins.begin(), plugins.end(), pluginName) != plugins.end();
}

} // namespace PluginSystem
