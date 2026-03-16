#include <gtest/gtest.h>
#include "McapLoader.h"

using namespace PluginSystem;

TEST(McapLoaderTest, GetName)     { McapLoader p; EXPECT_EQ(p.getName(), "MCAP Loader"); }
TEST(McapLoaderTest, GetVersion)  { McapLoader p; EXPECT_EQ(p.getVersion(), "1.0.9"); }
TEST(McapLoaderTest, OpenEmpty)   { McapLoader p; EXPECT_FALSE(p.open("")); }
TEST(McapLoaderTest, OpenFile)    { McapLoader p; EXPECT_TRUE(p.open("log.mcap")); EXPECT_FALSE(p.getChannels().empty()); }
