#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#include <string>
#include <vector>
#include <memory>

namespace PluginSystem {

class PluginInterface {
public:
    virtual ~PluginInterface() = default;

    virtual std::string getName() const = 0;
    virtual std::string getVersion() const = 0;
    virtual std::string getDescription() const = 0;
    virtual bool initialize() = 0;
    virtual void shutdown() = 0;
    virtual std::string execute(const std::string& input) = 0;
};

using PluginFactory = PluginInterface* (*)();

} // namespace PluginSystem

#ifdef _WIN32
    #define PLUGIN_EXPORT __declspec(dllexport)
#else
    #define PLUGIN_EXPORT __attribute__((visibility("default")))
#endif

extern "C" PLUGIN_EXPORT PluginSystem::PluginInterface* createPlugin();

#endif // PLUGIN_INTERFACE_H
