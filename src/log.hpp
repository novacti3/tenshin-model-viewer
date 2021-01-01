#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include <glad/glad.h>

enum LogLevel
{
    Info = 0, Warning, Error, Fatal
};

// TODO: Add severity filtering
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
    // NOTE: There has to be a better way to print messages. This reuses way too much code
    static void LogMessage(LogLevel severity, const char *message)
    {
        // if(_logFileStream.is_open())
        // {
        //     _logFileStream << message;
        // }

        // Get the current time in HH:MM:SS format
        time_t rawCurrentTime;
        time(&rawCurrentTime);
        tm *currentTime = localtime(&rawCurrentTime);

        char currentTimeStr[9];
        strftime(currentTimeStr, 9, "%T", currentTime);

        std::cout << "[" << currentTimeStr << "] " << message << std::endl;
    }
    static void LogMessage(LogLevel severity, const std::string &message)
    {
        // if(_logFileStream.is_open())
        // {
        //     _logFileStream << message;
        // }

        // Get the current time in HH:MM:SS format
        time_t rawCurrentTime;
        time(&rawCurrentTime);
        tm *currentTime = localtime(&rawCurrentTime);
        
        char currentTimeStr[9];
        strftime(currentTimeStr, 9, "%T", currentTime);

        std::cout << "[" << currentTimeStr << "] " << message << std::endl;
    }
};

static bool CheckError(char const* file, char const* function, int line)
{
    if (auto error = glGetError(); error != GL_NO_ERROR)
    {
        Log::LogError("OpenGL Error: " + std::to_string(error) + " : " + file + ":" + function + ":" + std::to_string(line));
        return false;
    }
    return true;
}

#define GL_CALL(x) x; CheckError(__FILE__, #x, __LINE__);