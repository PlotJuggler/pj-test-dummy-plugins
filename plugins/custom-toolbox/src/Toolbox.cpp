#include "Toolbox.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>

namespace PluginSystem {

Toolbox::Toolbox() {
    std::cout << "Custom Toolbox plugin created" << std::endl;
}

Toolbox::~Toolbox() {
    std::cout << "Custom Toolbox plugin destroyed" << std::endl;
}

std::string Toolbox::formatString(const std::string& pattern, const std::vector<std::string>& args) {
    std::string result = pattern;
    for (size_t i = 0; i < args.size(); ++i) {
        std::string placeholder = "{" + std::to_string(i) + "}";
        size_t pos = result.find(placeholder);
        if (pos != std::string::npos) {
            result.replace(pos, placeholder.length(), args[i]);
        }
    }
    return result;
}

size_t Toolbox::calculateHash(const std::string& input) {
    std::hash<std::string> hasher;
    return hasher(input);
}

bool Toolbox::validateInput(const std::string& input, const std::map<std::string, std::string>& rules) {
    if (input.empty()) {
        return false;
    }

    auto it = rules.find("min_length");
    if (it != rules.end()) {
        int minLength = std::stoi(it->second);
        if (input.length() < static_cast<size_t>(minLength)) {
            return false;
        }
    }

    it = rules.find("max_length");
    if (it != rules.end()) {
        int maxLength = std::stoi(it->second);
        if (input.length() > static_cast<size_t>(maxLength)) {
            return false;
        }
    }

    it = rules.find("allowed_chars");
    if (it != rules.end()) {
        const std::string& allowed = it->second;
        for (char c : input) {
            if (allowed.find(c) == std::string::npos) {
                return false;
            }
        }
    }

    return true;
}

std::string Toolbox::transformData(const std::string& data, const std::string& operation) {
    if (data.empty()) {
        return data;
    }

    std::string result = data;

    if (operation == "uppercase") {
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    } else if (operation == "lowercase") {
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    } else if (operation == "reverse") {
        std::reverse(result.begin(), result.end());
    } else if (operation == "trim") {
        auto start = result.find_first_not_of(" \t\n\r");
        auto end   = result.find_last_not_of(" \t\n\r");
        result = (start == std::string::npos) ? "" : result.substr(start, end - start + 1);
    } else if (operation == "capitalize") {
        if (!result.empty()) {
            result[0] = std::toupper(result[0]);
            for (size_t i = 1; i < result.length(); ++i) {
                result[i] = std::tolower(result[i]);
            }
        }
    } else {
        result = "Unknown operation: " + operation;
    }

    return result;
}

std::string Toolbox::getVersion() const {
    return m_version;
}

std::vector<std::string> Toolbox::getAvailableOperations() const {
    return m_operations;
}

} // namespace PluginSystem
