#pragma once


namespace SettingsKeys
{
    // KEY -> VALUE
    constexpr auto FLOORS_COUNT          = "FloorsCount";
    constexpr auto TYPE                  = "Type";
    constexpr auto NAME                  = "Name";
    constexpr auto RECEIVER              = "Receiver";
    constexpr auto HOST                  = "Host";
    constexpr auto PORT                  = "Port";
    constexpr auto DIR                   = "Dir";
    constexpr auto MAX_LOG_FILES         = "MaxLogFiles";
    constexpr auto MAX_LOG_FILES_SIZE_MB = "MaxLogFilesSizeMB";
    constexpr auto MAX_LOG_FILE_SIZE     = "MaxLogFileSize";

    // KEY -> SECTION
    constexpr auto SERVICE = "Service";
    constexpr auto LOGGING = "Logging";
}
