#include <cassert>
#include <SettingsLoader.hpp>
#include <fmt/core.h>
#include "Logger.hpp"


///// LOGGER_STREAM /////

Logger::LoggerStream::LoggerStream(const eP7Trace_Level level,
                                   const std::string& tag,
                                   const uint16_t line,
                                   const std::string& file,
                                   const std::string& function)
    : mLevel(level)
    , mTag(tag)
    , mLine(line)
    , mFile(file)
    , mFunction(function)
    , mStream()
{}

Logger::LoggerStream::~LoggerStream()
{
    Logger::Instance().P7Log(mLevel,
                             mTag,
                             mLine,
                             mFile,
                             mFunction,
                             mStream.str());
}

///// LOGGER /////

Logger::LoggerStream Logger::Log(const eP7Trace_Level level,
                                 const uint16_t line,
                                 const std::string& file,
                                 const std::string& function,
                                 const std::string& module)
{
    return LoggerStream(level,
                        module,
                        line,
                        file,
                        function);
}

Logger& Logger::Instance()
{
    static Logger logger;
    return logger;
}

Logger::Logger()
{
    Init();
}

Logger::~Logger()
{
    if (mP7Trace)
    {
        mP7Trace->Unregister_Thread(0);
    }
}

void Logger::Init()
{
    auto settings = SettingsLoader::GetSettings().logging;
    auto p7ArgsTemplate = "/P7.Sink={} /P7.Addr={} /P7.Port={} /P7.Roll={} /P7.Files={} /P7.FSize={}";
    auto p7Args = fmt::format(p7ArgsTemplate, settings.type,
                                              settings.receiver,
                                              settings.port,
                                              settings.maxFileSize,
                                              settings.maxFiles,
                                              settings.maxFilesSizeMB);

    mP7Client.reset(P7_Create_Client(TM(p7Args.c_str())));
    if (!mP7Client)
    {
        std::cerr << "Fail to create P7 client" << std::endl;
        return;
    }

    mP7Trace.reset(P7_Create_Trace(mP7Client.get(), TM("Trace channel 1")));
    if (!mP7Trace)
    {
        std::cerr << "Fail to create P7 trace" << std::endl;
        return;
    }

    mP7Trace->Register_Thread(TM("Application"), 0);
}

void Logger::P7Log(const eP7Trace_Level level,
                 const std::string& module,
                 const uint16_t line,
                 const std::string& file,
                 const std::string& function,
                 const std::string& message)
{
    if (!mP7Trace) {
        return;
    }

    if (mP7Modules.find(module) == mP7Modules.end()) {
        mP7Modules[module] = IP7_Trace::hModule();
        mP7Trace->Register_Module(TM(module.c_str()), &mP7Modules[module]);
    }

    mP7Trace->Trace_Managed(0,
                            level,
                            mP7Modules[module],
                            line,
                            file.c_str(),
                            function.c_str(),
                            message.c_str());
}
