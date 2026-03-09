#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include "PluginInterface.h"
#include <string>
#include <vector>

namespace PluginSystem {

class DataLoader : public PluginInterface {
public:
    DataLoader();
    ~DataLoader() override;

    std::string getName() const override;
    std::string getVersion() const override;
    std::string getDescription() const override;
    bool initialize() override;
    void shutdown() override;
    std::string execute(const std::string& input) override;

    std::vector<std::string> loadData(const std::string& source);
    bool validateData(const std::string& data);
    std::string processData(const std::string& data);

private:
    bool m_initialized = false;
    std::vector<std::string> m_loadedData;
};

} // namespace PluginSystem

#endif // DATA_LOADER_H
