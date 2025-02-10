#include <fstream>
#include <fmt/core.h>
#include <iostream>
#include "SettingsLoader.hpp"
#include "Keys.hpp"


using namespace SettingsKeys;


namespace
{
    constexpr auto VALUE_TYPE_STR = "string";
    constexpr auto VALUE_TYPE_NUM = "number";
    constexpr auto VALUE_TYPE_OBJ = "object";

    constexpr auto ROOT = "Root";

    constexpr auto CONFIG_NAME = "config.json";
}


Settings SettingsLoader::GetSettings()
{
    static Settings settings = Load();
    return settings;
}

Settings SettingsLoader::Load()
{
    Settings settings;

    try {
        std::ifstream config(CONFIG_NAME);
        json data = json::parse(config);

        return Settings {LoadValue<std::string>(data, SERVICE, ROOT, VALUE_TYPE_STR),
                         LoadLoggingSettings(data),
                         true};
    }
    catch (const Exception& e) {
        std::cout << "Invalid config. Error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Invalid config, unidentified error\n";
    }

    return Settings();
}

LoggingSettings SettingsLoader::LoadLoggingSettings(const json& settingsJson)
{
    json loggingSettingsJson = LoadValue<json>(settingsJson, LOGGING, ROOT, VALUE_TYPE_OBJ);

    return LoggingSettings {LoadValue<std::string>(loggingSettingsJson, TYPE, LOGGING, VALUE_TYPE_STR),
                            LoadValue<std::string>(loggingSettingsJson, NAME, LOGGING, VALUE_TYPE_STR),
                            LoadValue<std::string>(loggingSettingsJson, RECEIVER, LOGGING, VALUE_TYPE_STR),
                            LoadValue<uint16_t>(loggingSettingsJson, PORT, LOGGING, VALUE_TYPE_NUM),
                            LoadValue<std::string>(loggingSettingsJson, DIR, LOGGING, VALUE_TYPE_STR),
                            LoadValue<uint64_t>(loggingSettingsJson, MAX_LOG_FILES, LOGGING, VALUE_TYPE_NUM),
                            LoadValue<uint64_t>(loggingSettingsJson, MAX_LOG_FILES_SIZE_MB, LOGGING, VALUE_TYPE_NUM),
                            LoadValue<std::string>(loggingSettingsJson, MAX_LOG_FILE_SIZE, LOGGING, VALUE_TYPE_STR)};
}

template <typename T>
T SettingsLoader::LoadValue(const json& valueJson,
                            const std::string& key,
                            const std::string& section,
                            const std::string& type)
{
    if (!valueJson.contains(key)) {
        throw Exception {fmt::format("Key '{}' in section '{}' not found", key, section)};
    }

    auto value = valueJson[key];
    if (value.type_name() != type) {
        throw Exception {fmt::format("Key '{}' in section '{}' has an incorrect data type", key, section)};
    }

    return value;
}
