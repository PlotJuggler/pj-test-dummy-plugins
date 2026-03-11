#include <gtest/gtest.h>
#include "Ros2Streaming.h"

using namespace PluginSystem;

TEST(Ros2StreamingTest, GetName)           { Ros2Streaming p; EXPECT_EQ(p.getName(), "ROS 2 Streaming"); }
TEST(Ros2StreamingTest, GetVersion)        { Ros2Streaming p; EXPECT_EQ(p.getVersion(), "1.0.0"); }
TEST(Ros2StreamingTest, ConnectEmpty)      { Ros2Streaming p; EXPECT_FALSE(p.connect("")); }
TEST(Ros2StreamingTest, ConnectDisconnect) { Ros2Streaming p; EXPECT_TRUE(p.connect("localhost")); EXPECT_TRUE(p.isConnected()); p.disconnect(); EXPECT_FALSE(p.isConnected()); }
TEST(Ros2StreamingTest, TopicsConnected)   { Ros2Streaming p; p.connect("localhost"); EXPECT_FALSE(p.getTopics().empty()); }
