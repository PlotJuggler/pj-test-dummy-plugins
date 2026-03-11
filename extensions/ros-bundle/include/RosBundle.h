#ifndef ROS_BUNDLE_H
#define ROS_BUNDLE_H

#include <string>
#include <vector>

namespace PluginSystem {

class RosBundle {
public:
    RosBundle();
    ~RosBundle();
    std::string getName() const;
    std::string getVersion() const;
    std::vector<std::string> getIncludedPlugins() const;
    bool isAvailable(const std::string& pluginName) const;
};

} // namespace PluginSystem

#endif // ROS_BUNDLE_H
