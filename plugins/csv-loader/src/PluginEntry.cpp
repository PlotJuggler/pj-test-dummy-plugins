#include "CsvLoader.h"

extern "C" PluginSystem::CsvLoader* createCsvLoader() {
    return new PluginSystem::CsvLoader();
}
