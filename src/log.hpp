#pragma once

#include <iostream>
#include <string>
#include <fstream>

enum LogLevel
{
    Info = 0, Warning, Error, Fatal
};

// TODO: Add severity filtering
// TODO: Add a timestamp to the log message
// TODO: Add the message severity to the log message
// TODO: Add logging into file
class Log final
{
    private:
    // inline static std::string _logFilePath;
    // inline static std::fstream _logFileStream;

    private:
    Log() {}
    ~Log()
    {
        // DeInitFileLog();
    }

    public:
    // static bool InitFileLog(const std::string filePath)
    // {
    //     _logFilePath = filePath;

    //     _logFileStream.open(filePath, ios::);

    //     return Log::_logFileStream.is_open();
    // }

    // static void DeInitFileLog()
    // {
    //     if(_logFileStream.is_open())
    //     {
    //         _logFileStream.close();
    //     }
    // }

    static void LogInfo(const char *message)            { Log::LogMessage(LogLevel::Info, message); }
    static void LogInfo(const std::string &message)     { Log::LogMessage(LogLevel::Info, message); }

    static void LogWarning(const char *message)         { Log::LogMessage(LogLevel::Warning, message); }
    static void LogWarning(const std::string &message)  { Log::LogMessage(LogLevel::Warning, message); }

    static void LogError(const char *message)           { Log::LogMessage(LogLevel::Error, message); }
    static void LogError(const std::string &message)    { Log::LogMessage(LogLevel::Error, message); }

    static void LogFatal(const char *message)           { Log::LogMessage(LogLevel::Fatal, message); }
    static void LogFatal(const std::string &message)    { Log::LogMessage(LogLevel::Fatal, message); }

    private:
    static void LogMessage(LogLevel severity, const char *message)
    {
        // if(_logFileStream.is_open())
        // {
        //     _logFileStream << message;
        // }

        std::cout << message << std::endl;
    }
    static void LogMessage(LogLevel severity, const std::string &message)
    {
        // if(_logFileStream.is_open())
        // {
        //     _logFileStream << message;
        // }

        std::cout << message << std::endl;
    }
};