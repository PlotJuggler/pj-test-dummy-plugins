#include <algorithm>
#include <gtest/gtest.h>
#include "Toolbox.h"

using namespace PluginSystem;

class ToolboxTest : public ::testing::Test {
protected:
    void SetUp() override {
        toolbox = std::make_unique<Toolbox>();
    }
    void TearDown() override {
        toolbox.reset();
    }
    std::unique_ptr<Toolbox> toolbox;
};

TEST_F(ToolboxTest, GetVersion) {
    EXPECT_EQ(toolbox->getVersion(), "1.0.0");
}

TEST_F(ToolboxTest, FormatString) {
    std::vector<std::string> args = {"arg1", "arg2", "arg3"};
    std::string result = toolbox->formatString("Test {0} {1} {2}", args);
    EXPECT_EQ(result, "Test arg1 arg2 arg3");
}

TEST_F(ToolboxTest, CalculateHash) {
    size_t hash1 = toolbox->calculateHash("test");
    size_t hash2 = toolbox->calculateHash("test");
    size_t hash3 = toolbox->calculateHash("different");
    EXPECT_EQ(hash1, hash2);
    EXPECT_NE(hash1, hash3);
}

TEST_F(ToolboxTest, ValidateInput) {
    std::map<std::string, std::string> rules;
    rules["min_length"] = "3";
    rules["max_length"] = "10";
    EXPECT_TRUE(toolbox->validateInput("test", rules));
    EXPECT_FALSE(toolbox->validateInput("ab", rules));
    EXPECT_FALSE(toolbox->validateInput("verylongstring", rules));
}

TEST_F(ToolboxTest, TransformData) {
    EXPECT_EQ(toolbox->transformData("hello", "uppercase"), "HELLO");
    EXPECT_EQ(toolbox->transformData("HELLO", "lowercase"), "hello");
    EXPECT_EQ(toolbox->transformData("hello", "reverse"), "olleh");
    EXPECT_EQ(toolbox->transformData("  hello  ", "trim"), "hello");
    EXPECT_EQ(toolbox->transformData("hello world", "capitalize"), "Hello world");
}

TEST_F(ToolboxTest, GetAvailableOperations) {
    auto operations = toolbox->getAvailableOperations();
    EXPECT_FALSE(operations.empty());
    EXPECT_NE(std::find(operations.begin(), operations.end(), "uppercase"), operations.end());
}
