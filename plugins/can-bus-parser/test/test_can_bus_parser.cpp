#include <gtest/gtest.h>
#include "CanBusParser.h"

using namespace PluginSystem;

TEST(CanBusParserTest, GetName)       { CanBusParser p; EXPECT_EQ(p.getName(), "CAN Bus Parser"); }
TEST(CanBusParserTest, GetVersion)    { CanBusParser p; EXPECT_EQ(p.getVersion(), "1.0.0"); }
TEST(CanBusParserTest, LoadDbcEmpty)  { CanBusParser p; EXPECT_FALSE(p.loadDbc("")); }
TEST(CanBusParserTest, LoadDbc)       { CanBusParser p; EXPECT_TRUE(p.loadDbc("bus.dbc")); }
TEST(CanBusParserTest, ParseFrame)    { CanBusParser p; p.loadDbc("bus.dbc"); auto r = p.parseFrame(0x100, {0x42}); EXPECT_FALSE(r.empty()); }
