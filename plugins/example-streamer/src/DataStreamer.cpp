#include "DataStreamer.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

namespace PluginSystem {

DataStreamer::DataStreamer() {
    std::cout << "DataStreamer plugin created" << std::endl;
}

DataStreamer::~DataStreamer() {
    if (m_streaming) {
        stopStreaming();
    }
    std::cout << "DataStreamer plugin destroyed" << std::endl;
}

bool DataStreamer::startStreaming(const std::string& source) {
    if (m_streaming) {
        std::cout << "Already streaming from: " << m_currentSource << std::endl;
        return false;
    }

    m_currentSource = source;
    m_streaming = true;

    std::cout << "Started streaming from: " << source << std::endl;

    for (int i = 1; i <= 5; ++i) {
        if (!m_streaming) break;

        std::stringstream ss;
        ss << "stream_data_" << i << "_from_" << source;
        m_streamedData.push_back(ss.str());

        std::cout << "Streamed: " << ss.str() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return true;
}

void DataStreamer::stopStreaming() {
    if (!m_streaming) {
        return;
    }

    std::cout << "Stopping stream from: " << m_currentSource << std::endl;
    m_streaming = false;
    m_currentSource.clear();
}

std::vector<std::string> DataStreamer::getStreamedData() const {
    return m_streamedData;
}

bool DataStreamer::isStreaming() const {
    return m_streaming;
}

std::string DataStreamer::processStream(const std::string& data) {
    if (data.empty()) {
        return "Empty stream data";
    }
    return "[STREAM] " + data;
}

} // namespace PluginSystem
