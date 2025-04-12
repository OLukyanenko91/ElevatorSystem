#pragma once

#include <iostream>
#include <sstream>
#include <memory>
#include <map>
#include "P7_Trace.h"


#define lmDebug() Logger::Instance().Log(EP7TRACE_LEVEL_DEBUG, __LINE__, __FILE__, __FUNCTION__, LOG_MODULE_NAME)
#define lmInfo() Logger::Instance().Log(EP7TRACE_LEVEL_INFO, __LINE__, __FILE__, __FUNCTION__, LOG_MODULE_NAME)
#define lmWarning() Logger::Instance().Log(EP7TRACE_LEVEL_WARNING, __LINE__, __FILE__, __FUNCTION__, LOG_MODULE_NAME)
#define lmError() Logger::Instance().Log(EP7TRACE_LEVEL_ERROR, __LINE__, __FILE__, __FUNCTION__, LOG_MODULE_NAME)
#define lmCritical() Logger::Instance().Log(EP7TRACE_LEVEL_CRITICAL, __LINE__, __FILE__, __FUNCTION__, LOG_MODULE_NAME)
#define lmEnter() Logger::Instance().Log(EP7TRACE_LEVEL_INFO, __LINE__, __FILE__, __FUNCTION__, LOG_MODULE_NAME) << "Enter"
#define lDebug() Logger::Instance().Log(EP7TRACE_LEVEL_DEBUG, __LINE__, __FILE__, __FUNCTION__)
#define lInfo() Logger::Instance().Log(EP7TRACE_LEVEL_INFO, __LINE__, __FILE__, __FUNCTION__)
#define lWarning() Logger::Instance().Log(EP7TRACE_LEVEL_WARNING, __LINE__, __FILE__, __FUNCTION__)
#define lError() Logger::Instance().Log(EP7TRACE_LEVEL_ERROR, __LINE__, __FILE__, __FUNCTION__)
#define lCritical() Logger::Instance().Log(EP7TRACE_LEVEL_CRITICAL, __LINE__, __FILE__, __FUNCTION__)
#define lEnter() Logger::Instance().Log(EP7TRACE_LEVEL_INFO, __LINE__, __FILE__, __FUNCTION__) << "Enter"

class Logger
{
private:
    class LoggerStream {
    public:
        LoggerStream(const eP7Trace_Level level,
                     const std::string& tag,
                     const uint16_t line,
                     const std::string& file,
                     const std::string& function);
        ~LoggerStream();

        template <typename T>
        LoggerStream& operator<<(const T& value) {
            mStream << value;
            return *this;
        }

    private:
        eP7Trace_Level     mLevel;
        std::string        mTag;
        uint16_t           mLine;
        std::string        mFile;
        std::string        mFunction;
        std::ostringstream mStream;
    };

    friend class LoggerStream;

public:
    LoggerStream Log(const eP7Trace_Level level,
                     const uint16_t line,
                     const std::string& file,
                     const std::string& function,
                     const std::string& module = "Undefined");

public:
    static Logger& Instance();

private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    void Init();
    void P7Log(const eP7Trace_Level level,
               const std::string& module,
               const uint16_t line,
               const std::string& file,
               const std::string& function,
               const std::string& message);

private:
    std::unique_ptr<IP7_Client>               mP7Client;
    std::unique_ptr<IP7_Trace>                mP7Trace;
    std::map<std::string, IP7_Trace::hModule> mP7Modules;
};
