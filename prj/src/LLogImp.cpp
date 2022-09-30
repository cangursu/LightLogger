
// clang-format off


#include "LLogImp.h"

#include <iostream>
#include <cstring>



LoggerImp::LLogLevelType LoggerImp::_logLevelEnv = LLogLevelType::TRACE;



inline std::string nowStr ()
{
    timespec    tsNow {};
    tm          tmNow {};

    clock_gettime(CLOCK_REALTIME, &tsNow);
    gmtime_r(&tsNow.tv_sec, &tmNow);
    std::ostringstream ss;
    //ss << (tmNow.tm_year + 1900) << "." << tmNow.tm_mon << "." << tmNow.tm_mday;
    //ss << " - "
    ss << tmNow.tm_hour << ":" <<  tmNow.tm_min << ":" << tmNow.tm_sec << "." << tsNow.tv_nsec;
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
        (*this) << "[" <<  to_string(type) <<  "] ";

    if (Flag_AddTimeStamp())
        (*this)  << nowStr() << " - ";
}



LoggerImp::LoggerImp (LLogLevelType type, const std::string &msg,
                      flag_t opt /*= 0xff*/)
    : LoggerImp(type, opt)
{
    (*this) << msg << " - ";
}



LoggerImp::~LoggerImp ()
{
    if (Flag_DispConsole())
        std::cout << LogText() << ((false == Flag_AddLineFeed())?"\n": "");
}



std::string LoggerImp::LogText()
{
    if (Flag_AddLineFeed())
        _sstream << ('\n');
    return std::move(_sstream.str());
}



void LoggerImp::LLogLevel (LoggerImp::LLogLevelType level)
{
    LoggerImp::_logLevelEnv = level;
}



LoggerImp::LLogLevelType LoggerImp::LLogLevel ()
{
    return LoggerImp::_logLevelEnv;
}



std::string to_string (LoggerImp::LLogLevelType type)
{
    switch(type)
    {
        case LoggerImp::LLogLevelType::DEBUG      : return "DEBUG"    ;
        case LoggerImp::LLogLevelType::TRACE      : return "TRACE"    ;
        case LoggerImp::LLogLevelType::INFO       : return "INFO"     ;
        case LoggerImp::LLogLevelType::WARN       : return "WARN"     ;
        case LoggerImp::LLogLevelType::ERROR      : return "ERROR"    ;
        case LoggerImp::LLogLevelType::CRITICAL   : return "CRITICAL" ;
    }
    return "NA   ";
}



// clang-format on
