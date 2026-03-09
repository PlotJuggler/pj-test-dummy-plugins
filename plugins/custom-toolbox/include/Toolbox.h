#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <string>
#include <vector>
#include <map>

namespace PluginSystem {

class Toolbox {
public:
    Toolbox();
    ~Toolbox();

    std::string formatString(const std::string& pattern, const std::vector<std::string>& args);
    size_t calculateHash(const std::string& input);
    bool validateInput(const std::string& input, const std::map<std::string, std::string>& rules);
    std::string transformData(const std::string& data, const std::string& operation);
    std::string getVersion() const;
    std::vector<std::string> getAvailableOperations() const;

private:
    std::string m_version = "1.0.0";
    std::vector<std::string> m_operations = {
        "uppercase", "lowercase", "reverse", "trim", "capitalize"
    };
};

} // namespace PluginSystem

#endif // TOOLBOX_H
