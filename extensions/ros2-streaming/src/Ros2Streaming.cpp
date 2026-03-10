#include "Ros2Streaming.h"

namespace PluginSystem {

Ros2Streaming::Ros2Streaming() {}
Ros2Streaming::~Ros2Streaming() { disconnect(); }
std::string Ros2Streaming::getName() const { return "ROS 2 Streaming"; }
std::string Ros2Streaming::getVersion() const { return "1.0.0"; }

bool Ros2Streaming::connect(const std::string& host) {
    if (host.empty()) return false;
    m_connected = true;
    return true;
}

void Ros2Streaming::disconnect() { m_connected = false; }
bool Ros2Streaming::isConnected() const { return m_connected; }
std::vector<std::string> Ros2Streaming::getTopics() const {
    if (!m_connected) return {};
    return {"/topic_a", "/topic_b"};
}

} // namespace PluginSystem
