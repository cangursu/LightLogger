
// clang-format off

#ifndef __LIGHT_LOGGER_H__
#define __LIGHT_LOGGER_H__

#include "LLogImp.h"

#include <iostream>


#define LLOG_ERROR   LogError     ( LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE)) )
#define LLOG_WARN    LogWarn      ( LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE)) )
#define LLOG_INFO    LogInfo      ( LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE)) )
#define LLOG_DEBUG   LogDebug     ( LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE)) )
#define LLOG_TRACE   LogTrace     ( LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE)) )
#define LLOG_CRITC   LogCritical  ( LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE)) )





class LogError : public LoggerImp
{
    public :
        LogError(const std::string &msg, LoggerImp::flag_t flags)
            : LoggerImp(LoggerImp::LLogLevelType::ERROR, msg, flags)
        {
        }
        ~LogError()
        {
            std::cout << LogText();
        }
};


class LogWarn : public LoggerImp
{
    public :
        LogWarn(const std::string &msg, LoggerImp::flag_t flags)
            : LoggerImp(LoggerImp::LLogLevelType::WARN, msg, flags)
        {
        }
        ~LogWarn()
        {
            std::cout << LogText();
        }
};


class LogInfo : public LoggerImp
{
    public :
        LogInfo(const std::string &msg, LoggerImp::flag_t flags)
            :  LoggerImp(LoggerImp::LLogLevelType::INFO, msg, flags)
        {
        }
        ~LogInfo()
        {
            std::cout << LogText();
        }
};


class LogDebug : public LoggerImp
{
    public :
        LogDebug(const std::string &msg, LoggerImp::flag_t flags)
            :  LoggerImp(LoggerImp::LLogLevelType::DEBUG, msg, flags)
        {
        }
        ~LogDebug()
        {
            std::cout << LogText();
        }
};


class LogTrace : public LoggerImp
{
    public :
        LogTrace(const std::string &msg, LoggerImp::flag_t flags)
            : LoggerImp(LoggerImp::LLogLevelType::TRACE, msg, flags)
        {
        }
        ~LogTrace()
        {
            std::cout << LogText();
        }

};



class LogCritical : public LoggerImp
{
    public :
        LogCritical(const std::string &msg, LoggerImp::flag_t flags)
            : LoggerImp(LoggerImp::LLogLevelType::CRITICAL, msg, flags)
        {
        }
        ~LogCritical()
        {
            std::cout << LogText();
        }

};



#endif // __LIGHT_LOGGER_H__

// clang-format on
