#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include <string>
#include <vector>

namespace PluginSystem {

class CsvLoader {
public:
    CsvLoader();
    ~CsvLoader();
    std::string getName() const;
    std::string getVersion() const;
    bool load(const std::string& filepath);
    std::vector<std::string> getColumns() const;

private:
    std::vector<std::string> m_columns;
};

} // namespace PluginSystem

#endif // CSV_LOADER_H
