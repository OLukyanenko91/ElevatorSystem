#pragma once

#include <nlohmann/json.hpp>
#include "Settings.hpp"


using json = nlohmann::json;


class SettingsLoader
{
    class Exception : public std::runtime_error
    {
    public:
        Exception(const char* message)
            : std::runtime_error(message) {
        }

        Exception(const std::string& message)
            : std::runtime_error(message) {
        }
    };


public:
    static Settings GetSettings();

private:
    SettingsLoader() = delete;
    ~SettingsLoader() = delete;
    SettingsLoader(const SettingsLoader&) = delete;
    SettingsLoader& operator=(const SettingsLoader&) = delete;

private:
    static Settings        Load();
    static LoggingSettings LoadLoggingSettings(const json& settingsJson);

    template <typename T>
    static T LoadValue(const json& valueJson,
                       const std::string& key,
                       const std::string& section,
                       const std::string& type);

private:
    static Settings mSettings;
};
