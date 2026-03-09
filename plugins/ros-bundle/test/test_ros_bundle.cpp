#include <algorithm>
#include <gtest/gtest.h>
#include "RosBundle.h"

using namespace PluginSystem;

TEST(RosBundleTest, GetName)          { RosBundle p; EXPECT_EQ(p.getName(), "ROS Bundle"); }
TEST(RosBundleTest, GetVersion)       { RosBundle p; EXPECT_EQ(p.getVersion(), "1.0.0"); }
TEST(RosBundleTest, IncludedPlugins)  { RosBundle p; EXPECT_FALSE(p.getIncludedPlugins().empty()); }
TEST(RosBundleTest, IsAvailable)      { RosBundle p; EXPECT_TRUE(p.isAvailable("ros2-streaming")); }
TEST(RosBundleTest, IsNotAvailable)   { RosBundle p; EXPECT_FALSE(p.isAvailable("unknown-plugin")); }
