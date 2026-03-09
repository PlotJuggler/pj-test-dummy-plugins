#include "FftToolbox.h"

extern "C" PluginSystem::FftToolbox* createFftToolbox() {
    return new PluginSystem::FftToolbox();
}
