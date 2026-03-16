#include "McapLoader.h"

namespace PluginSystem {

McapLoader::McapLoader() {}
McapLoader::~McapLoader() {}
std::string McapLoader::getName() const { return "MCAP Loader"; }
std::string McapLoader::getVersion() const { return "1.0.9"; }

bool McapLoader::open(const std::string& filepath) {
    if (filepath.empty()) return false;
    m_channels = {"channel_0", "channel_1"};
    return true;
}

std::vector<std::string> McapLoader::getChannels() const { return m_channels; }

} // namespace PluginSystem
