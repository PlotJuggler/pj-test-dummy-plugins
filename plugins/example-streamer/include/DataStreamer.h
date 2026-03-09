#ifndef DATA_STREAMER_H
#define DATA_STREAMER_H

#include <string>
#include <vector>
#include <memory>

namespace PluginSystem {

class DataStreamer {
public:
    DataStreamer();
    ~DataStreamer();

    bool startStreaming(const std::string& source);
    void stopStreaming();
    std::vector<std::string> getStreamedData() const;
    bool isStreaming() const;
    std::string processStream(const std::string& data);

private:
    bool m_streaming = false;
    std::vector<std::string> m_streamedData;
    std::string m_currentSource;
};

} // namespace PluginSystem

#endif // DATA_STREAMER_H
