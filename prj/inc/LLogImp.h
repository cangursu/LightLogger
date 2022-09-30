
// clang-format off


#ifndef __LIGHT_LOGGER_IMPL_H__
#define __LIGHT_LOGGER_IMPL_H__


#include <sstream>

#include <iostream> //TODO: DO_NOT_PUSH
#include <bitset> //TODO: DO_NOT_PUSH



// #define LLOG_DEBUG   LoggerImp (LoggerImp::DEBUG  , LLogMsg (__FILE__, __LINE__, __PRETTY_FUNCTION__) )
// #define LLOG_TRACE   LoggerImp (LoggerImp::TRACE  , LLogMsg (__FILE__, __LINE__, __PRETTY_FUNCTION__) )
// #define LLOG_INFO    LoggerImp (LoggerImp::INFO   , LLogMsg (__FILE__, __LINE__, __PRETTY_FUNCTION__) )
// #define LLOG_WARN    LoggerImp (LoggerImp::WARN   , LLogMsg (__FILE__, __LINE__, __PRETTY_FUNCTION__) )
// #define LLOG_ERROR   LoggerImp (LoggerImp::ERROR  , LLogMsg (__FILE__, __LINE__, __PRETTY_FUNCTION__) )




std::string LLogMsg(const char *file, int line, const char *func);

class LoggerImp
{

public:

    enum class LLogLevelType
    {
        DEBUG,
        TRACE,
        INFO,
        WARN,
        ERROR,
        CRITICAL,
    };

    using flag_t = uint16_t;
    enum class LLogFlags : flag_t
    {
        NONE          = 0x00,
        ADD_LEVEL_TAG = (0x01 << 0),
        ADD_TIMESTAMP = (0x01 << 1),
        ADD_FILELINE  = (0x01 << 2),
        ADD_LINEFEED  = (0x01 << 3),
        DISP_CONSOLE  = (0x01 << 4),
        ALL           = 0xff
    };


    LoggerImp(LLogLevelType type, flag_t flags = static_cast<flag_t>(LLogFlags::ALL));
    LoggerImp(LLogLevelType type, const std::string &msg, flag_t flags = static_cast<flag_t>(LLogFlags::ALL));
    virtual ~LoggerImp();

    LoggerImp()                     = delete;
    LoggerImp(const LoggerImp &)    = delete;
    LoggerImp(LoggerImp &&)         = delete;

    static void             LLogLevel(LLogLevelType level);
    static LLogLevelType    LLogLevel();

    bool Flag_AddLevelTag() const       { return Flag(LLogFlags::ADD_LEVEL_TAG);        }
    bool Flag_AddTimeStamp() const      { return Flag(LLogFlags::ADD_TIMESTAMP);        }
    bool Flag_AddFileLine() const       { return Flag(LLogFlags::ADD_FILELINE);         }
    bool Flag_AddLineFeed() const       { return Flag(LLogFlags::ADD_LINEFEED);         }
    bool Flag_DispConsole() const       { return Flag(LLogFlags::DISP_CONSOLE);         }

    bool Flag(LLogFlags flgitem) const  { return static_cast<flag_t>(_flags) & static_cast<flag_t>(flgitem);    }
    void FlagSet(LLogFlags flgitem)     { _flags |= static_cast<LoggerImp::flag_t>(flgitem);                    }
    void FlagReset(LLogFlags flgitem)   { _flags &= ~static_cast<LoggerImp::flag_t>(flgitem);                   }



    virtual std::string     LogText();

    template<class T> LoggerImp &operator << (const T &msg)
    {
        if(_logLevel >= LLogLevel())
        {
            _sstream << msg;
        }
        return *this;
    }
private:
    LLogLevelType           _logLevel   = LLogLevelType::TRACE;
    std::ostringstream      _sstream;
    flag_t                  _flags      = static_cast<flag_t>(LLogFlags::ALL);

    static LLogLevelType    _logLevelEnv;
};

std::string to_string(LoggerImp::LLogLevelType type);




#endif //__LIGHT_LOGGER_IMPL_H__

// clang-format on
