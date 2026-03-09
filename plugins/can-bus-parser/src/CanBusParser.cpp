#include "CanBusParser.h"

namespace PluginSystem {

CanBusParser::CanBusParser() {}
CanBusParser::~CanBusParser() {}
std::string CanBusParser::getName() const { return "CAN Bus Parser"; }
std::string CanBusParser::getVersion() const { return "1.0.0"; }

bool CanBusParser::loadDbc(const std::string& dbcPath) {
    if (dbcPath.empty()) return false;
    m_dbcLoaded = true;
    return true;
}

std::map<std::string, double> CanBusParser::parseFrame(uint32_t id, const std::vector<uint8_t>& data) {
    if (!m_dbcLoaded || data.empty()) return {};
    return {{"signal_" + std::to_string(id), static_cast<double>(data[0])}};
}

} // namespace PluginSystem
