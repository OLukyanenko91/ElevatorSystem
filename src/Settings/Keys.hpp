#pragma once


namespace SettingsKeys
{
    // KEY -> VALUE
    constexpr auto SERVICE               = "Service";
    constexpr auto TYPE                  = "Type";
    constexpr auto NAME                  = "Name";
    constexpr auto RECEIVER              = "Receiver";
    constexpr auto PORT                  = "Port";
    constexpr auto DIR                   = "Dir";
    constexpr auto MAX_LOG_FILES         = "MaxLogFiles";
    constexpr auto MAX_LOG_FILES_SIZE_MB = "MaxLogFilesSizeMB";
    constexpr auto MAX_LOG_FILE_SIZE     = "MaxLogFileSize";

    // KEY -> SECTION
    constexpr auto LOGGING = "Logging";
}
