#include "DataLoader.h"
#include <iostream>
#include <sstream>
#include <algorithm>

namespace PluginSystem {

DataLoader::DataLoader() {
    std::cout << "DataLoader plugin created" << std::endl;
}

DataLoader::~DataLoader() {
    if (m_initialized) {
        shutdown();
    }
    std::cout << "DataLoader plugin destroyed" << std::endl;
}

std::string DataLoader::getName() const {
    return "Example Data Loader";
}

std::string DataLoader::getVersion() const {
    return "1.0.0";
}

std::string DataLoader::getDescription() const {
    return "Loads and processes data from various sources";
}

bool DataLoader::initialize() {
    if (m_initialized) {
        return true;
    }
    std::cout << "Initializing DataLoader plugin..." << std::endl;
    m_initialized = true;
    return true;
}

void DataLoader::shutdown() {
    if (!m_initialized) {
        return;
    }
    std::cout << "Shutting down DataLoader plugin..." << std::endl;
    m_loadedData.clear();
    m_initialized = false;
}

std::string DataLoader::execute(const std::string& input) {
    if (!m_initialized) {
        return "Error: Plugin not initialized";
    }
    std::cout << "DataLoader executing with input: " << input << std::endl;
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return "Processed: " + result;
}

std::vector<std::string> DataLoader::loadData(const std::string& source) {
    std::vector<std::string> data;
    if (source == "test") {
        data = {"item1", "item2", "item3", "item4", "item5"};
    } else if (source == "sample") {
        data = {"sample1", "sample2", "sample3"};
    } else {
        std::stringstream ss(source);
        std::string item;
        while (std::getline(ss, item, ',')) {
            if (!item.empty()) {
                data.push_back(item);
            }
        }
    }
    m_loadedData.insert(m_loadedData.end(), data.begin(), data.end());
    return data;
}

bool DataLoader::validateData(const std::string& data) {
    return !data.empty();
}

std::string DataLoader::processData(const std::string& data) {
    if (!validateData(data)) {
        return "Invalid data";
    }
    return "Processed: " + data;
}

} // namespace PluginSystem
