#include "FftToolbox.h"

extern "C" {

PluginSystem::FftToolbox* createFftToolbox() {
    return new PluginSystem::FftToolbox();
}

const char* getMetadata() {
    return R"({
        "id": "fft-toolbox",
        "name": "FFT Toolbox",
        "version": "1.0.9",
        "description": "Computes FFT over sample vectors with configurable window functions",
        "category": "toolbox",
        "min_plotjuggler_version": "4.0.0"
    })";
}

}
