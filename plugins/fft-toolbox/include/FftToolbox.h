#ifndef FFT_TOOLBOX_H
#define FFT_TOOLBOX_H

#include <string>
#include <vector>

namespace PluginSystem {

class FftToolbox {
public:
    FftToolbox();
    ~FftToolbox();
    std::string getName() const;
    std::string getVersion() const;
    std::vector<double> compute(const std::vector<double>& samples);
    std::vector<std::string> getAvailableWindows() const;

private:
    std::vector<std::string> m_windows = {"hann", "hamming", "rectangular"};
};

} // namespace PluginSystem

#endif // FFT_TOOLBOX_H
