#ifndef MCAP_LOADER_H
#define MCAP_LOADER_H

#include <string>
#include <vector>

namespace PluginSystem {

class McapLoader {
public:
    McapLoader();
    ~McapLoader();
    std::string getName() const;
    std::string getVersion() const;
    bool open(const std::string& filepath);
    std::vector<std::string> getChannels() const;

private:
    std::vector<std::string> m_channels;
};

} // namespace PluginSystem

#endif // MCAP_LOADER_H
