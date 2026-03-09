#include "FftToolbox.h"

namespace PluginSystem {

FftToolbox::FftToolbox() {}
FftToolbox::~FftToolbox() {}
std::string FftToolbox::getName() const { return "FFT Toolbox"; }
std::string FftToolbox::getVersion() const { return "1.0.0"; }

std::vector<double> FftToolbox::compute(const std::vector<double>& samples) {
    if (samples.empty()) return {};
    return std::vector<double>(samples.size() / 2 + 1, 0.0);
}

std::vector<std::string> FftToolbox::getAvailableWindows() const { return m_windows; }

} // namespace PluginSystem
