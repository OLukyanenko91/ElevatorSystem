#pragma once

#include <string>


struct LoggingSettings
{
    std::string type {"FileBin"};
    std::string instanceName {"ElevatorSystem"};
    std::string receiver {"0.0.0.0"};
    uint16_t    port {9010};
    std::string dir;
    uint64_t    maxFiles {20};
    uint64_t    maxFilesSizeMB {200};
    std::string maxFileSize {"10mb"};
};


struct Settings
{
    std::string     service;
    LoggingSettings logging;

    bool valid {false};
};
