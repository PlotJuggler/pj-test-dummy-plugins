#ifndef ROS2_STREAMING_H
#define ROS2_STREAMING_H

#include <string>
#include <vector>

namespace PluginSystem {

class Ros2Streaming {
public:
    Ros2Streaming();
    ~Ros2Streaming();
    std::string getName() const;
    std::string getVersion() const;
    bool connect(const std::string& host);
    void disconnect();
    bool isConnected() const;
    std::vector<std::string> getTopics() const;

private:
    bool m_connected = false;
};

} // namespace PluginSystem

#endif // ROS2_STREAMING_H
