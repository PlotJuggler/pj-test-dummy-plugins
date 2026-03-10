#ifndef CAN_BUS_PARSER_H
#define CAN_BUS_PARSER_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace PluginSystem {

class CanBusParser {
public:
    CanBusParser();
    ~CanBusParser();
    std::string getName() const;
    std::string getVersion() const;
    bool loadDbc(const std::string& dbcPath);
    std::map<std::string, double> parseFrame(uint32_t id, const std::vector<uint8_t>& data);

private:
    bool m_dbcLoaded = false;
};

} // namespace PluginSystem

#endif // CAN_BUS_PARSER_H
