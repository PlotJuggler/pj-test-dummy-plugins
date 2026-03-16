#include "CsvLoader.h"

namespace PluginSystem {

CsvLoader::CsvLoader() {}
CsvLoader::~CsvLoader() {}
std::string CsvLoader::getName() const { return "CSV Loader"; }
std::string CsvLoader::getVersion() const { return "1.0.9"; }

bool CsvLoader::load(const std::string& filepath) {
    if (filepath.empty()) return false;
    m_columns = {"timestamp", "value_a", "value_b"};
    return true;
}

std::vector<std::string> CsvLoader::getColumns() const { return m_columns; }

} // namespace PluginSystem
