
// clang-format off


#include "LLogImp.h"
#include "TimeFrame.h"

#include <iostream>
#include <iomanip>
#include <cstring>
#include <unistd.h>


LoggerImp::LLogLevelType LoggerImp::_logLevelEnv        = LLogLevelType::TRACE;
LoggerImp::LLogLevelType LoggerImp::_logLevelEnvConsole = LLogLevelType::TRACE;



inline std::string nowStr (bool date = false)
{
    timespec tsNow {};
    clock_gettime(CLOCK_REALTIME, &tsNow);;

    std::ostringstream ss;
    TimespecText2(tsNow, ss, date);
    return ss.str();
}


std::string LLogMsg (const char *file, int line, const char *func)
{
    const char *fileName = std::strrchr(file, '/');
    fileName = fileName ? fileName + 1 : file;

    const char *funcName = std::strchr(func, ' ');
    funcName = funcName ? funcName + 1 : func;

    const char *tmp = strchr(funcName, '(');
    size_t funcNameLentgth = (nullptr == tmp) ? std::strlen(funcName) : (tmp - funcName);

    std::ostringstream ss;
    ss << fileName << ":" << line << " (";
    ss.write(funcName, funcNameLentgth);
    ss << ")";
    return ss.str();
}


LoggerImp::LoggerImp (LLogLevelType type, flag_t opt /*= 0xff*/)
    : _logLevel (type)
    , _flags  (static_cast<flag_t>(opt))
{
    if (Flag_AddLevelTag())
        (*this) << "[" <<  to_string(type)  << "] ";

    if (Flag_AppProcessID())
        (*this) << "[" <<  getpid()  << "] ";

    if (Flag_AppThreadID())
        (*this) << "[" <<  gettid()  << "] ";

    if (Flag_AddTimeStamp())
        (*this)  << nowStr(Flag_AddDate()) << " - ";
}


LoggerImp::LoggerImp (LLogLevelType type, const std::string &msg,
                      flag_t opt /*= 0xff*/)
    : LoggerImp(type, opt)
{
    (*this) << msg << " - ";
}


LoggerImp::~LoggerImp ()
{
    if (Flag_DispConsole() && (LLogDoConsole(_logLevel)))
        std::cout << LogText();
}


std::string LoggerImp::LogText()
{
    std::string txt;
    if (LLogDo(_logLevel) || LLogDoConsole(_logLevel))
    {
        txt = _sstream.str();
        if (Flag_AddLineFeed())
            txt += ('\n');
    }
    return txt;
}


void LoggerImp::LLogLevel (LoggerImp::LLogLevelType level)
{
    LoggerImp::LLogLevel(level, level);
}

void LoggerImp::LLogLevel(LLogLevelType level, LLogLevelType levelConsole)
{
    LoggerImp::_logLevelEnv        = level;
    LoggerImp::_logLevelEnvConsole = levelConsole;
}


bool LoggerImp::LLogDo(LLogLevelType type)
{
    return type >= LoggerImp::_logLevelEnv;
}


bool LoggerImp::LLogDoConsole(LLogLevelType type)
{
    return type >= LoggerImp::_logLevelEnvConsole;
}


std::string to_string (LoggerImp::LLogLevelType type)
{
    switch(type)
    {
        case LoggerImp::LLogLevelType::TRACE    : return "TRACE"    ;
        case LoggerImp::LLogLevelType::DEBUG    : return "DEBUG"    ;
        case LoggerImp::LLogLevelType::INFO     : return "INFO"     ;
        case LoggerImp::LLogLevelType::WARN     : return "WARN"     ;
        case LoggerImp::LLogLevelType::ERROR    : return "ERROR"    ;
        case LoggerImp::LLogLevelType::FATAL    : return "FATAL"    ;
    }
    return "NA   ";
}



// clang-format on
