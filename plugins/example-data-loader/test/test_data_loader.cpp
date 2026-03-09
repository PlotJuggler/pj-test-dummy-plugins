#include <gtest/gtest.h>
#include "DataLoader.h"

using namespace PluginSystem;

class DataLoaderTest : public ::testing::Test {
protected:
    void SetUp() override {
        loader = std::make_unique<DataLoader>();
    }
    void TearDown() override {
        loader.reset();
    }
    std::unique_ptr<DataLoader> loader;
};

TEST_F(DataLoaderTest, GetName) {
    EXPECT_EQ(loader->getName(), "Example Data Loader");
}

TEST_F(DataLoaderTest, GetVersion) {
    EXPECT_EQ(loader->getVersion(), "1.0.0");
}

TEST_F(DataLoaderTest, GetDescription) {
    EXPECT_FALSE(loader->getDescription().empty());
}

TEST_F(DataLoaderTest, Initialize) {
    EXPECT_TRUE(loader->initialize());
}

TEST_F(DataLoaderTest, Execute) {
    loader->initialize();
    std::string result = loader->execute("test");
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("Processed"), std::string::npos);
}

TEST_F(DataLoaderTest, ValidateData) {
    EXPECT_TRUE(loader->validateData("valid data"));
    EXPECT_FALSE(loader->validateData(""));
}

TEST_F(DataLoaderTest, ProcessData) {
    std::string result = loader->processData("test");
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("Processed"), std::string::npos);
}

TEST_F(DataLoaderTest, LoadData) {
    auto data = loader->loadData("test");
    EXPECT_EQ(data.size(), 5u);
    EXPECT_EQ(data[0], "item1");
    EXPECT_EQ(data[4], "item5");
}
