#include <gtest/gtest.h>
#include "CsvLoader.h"

using namespace PluginSystem;

TEST(CsvLoaderTest, GetName)    { CsvLoader p; EXPECT_EQ(p.getName(), "CSV Loader"); }
TEST(CsvLoaderTest, GetVersion) { CsvLoader p; EXPECT_EQ(p.getVersion(), "1.0.0"); }
TEST(CsvLoaderTest, LoadEmpty)  { CsvLoader p; EXPECT_FALSE(p.load("")); }
TEST(CsvLoaderTest, LoadFile)   { CsvLoader p; EXPECT_TRUE(p.load("data.csv")); EXPECT_FALSE(p.getColumns().empty()); }
