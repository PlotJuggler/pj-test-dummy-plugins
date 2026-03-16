#include "CsvLoader.h"

extern "C" {

PluginSystem::CsvLoader* createCsvLoader() {
    return new PluginSystem::CsvLoader();
}

const char* getMetadata() {
    return R"({
        "id": "csv-loader",
        "name": "CSV Loader",
        "version": "1.0.9",
        "description": "Loads CSV files and exposes column names",
        "category": "data_loader",
        "min_plotjuggler_version": "4.0.0"
    })";
}

}
