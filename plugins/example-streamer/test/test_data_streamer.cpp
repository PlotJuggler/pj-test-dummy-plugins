#include <gtest/gtest.h>
#include "DataStreamer.h"

using namespace PluginSystem;

class DataStreamerTest : public ::testing::Test {
protected:
    void SetUp() override {
        streamer = std::make_unique<DataStreamer>();
    }
    void TearDown() override {
        streamer.reset();
    }
    std::unique_ptr<DataStreamer> streamer;
};

TEST_F(DataStreamerTest, StartStreaming) {
    EXPECT_TRUE(streamer->startStreaming("test_source"));
}

TEST_F(DataStreamerTest, IsStreaming) {
    EXPECT_FALSE(streamer->isStreaming());
    streamer->startStreaming("test");
    EXPECT_TRUE(streamer->isStreaming());
}

TEST_F(DataStreamerTest, StopStreaming) {
    streamer->startStreaming("test");
    EXPECT_TRUE(streamer->isStreaming());
    streamer->stopStreaming();
    EXPECT_FALSE(streamer->isStreaming());
}

TEST_F(DataStreamerTest, GetStreamedData) {
    streamer->startStreaming("test");
    auto data = streamer->getStreamedData();
    EXPECT_FALSE(data.empty());
}

TEST_F(DataStreamerTest, ProcessStream) {
    std::string result = streamer->processStream("test data");
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("[STREAM]"), std::string::npos);
}
