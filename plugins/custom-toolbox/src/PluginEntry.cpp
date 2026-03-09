#include "Toolbox.h"

extern "C" PluginSystem::Toolbox* createToolbox() {
    return new PluginSystem::Toolbox();
}
