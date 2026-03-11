#include <gtest/gtest.h>
#include "FftToolbox.h"

using namespace PluginSystem;

TEST(FftToolboxTest, GetName)      { FftToolbox p; EXPECT_EQ(p.getName(), "FFT Toolbox"); }
TEST(FftToolboxTest, GetVersion)   { FftToolbox p; EXPECT_EQ(p.getVersion(), "1.0.0"); }
TEST(FftToolboxTest, ComputeEmpty) { FftToolbox p; EXPECT_TRUE(p.compute({}).empty()); }
TEST(FftToolboxTest, ComputeSamples) { FftToolbox p; auto r = p.compute({1.0, 2.0, 3.0, 4.0}); EXPECT_FALSE(r.empty()); }
TEST(FftToolboxTest, Windows)      { FftToolbox p; EXPECT_FALSE(p.getAvailableWindows().empty()); }
