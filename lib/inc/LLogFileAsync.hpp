
#ifndef __LIGHT_LOGGER_FILE_ASYNC_HPP__
#define __LIGHT_LOGGER_FILE_ASYNC_HPP__

#include "LLogImp.h"
#include "LLogFileUtil.hpp"
#include "WorkQueue.h"

#include <string>


// Queue Declarations

struct WQLogFileItem
{
    LoggerImp::LLogLevelType    _type;
    std::string                 _txt;
};

int WQLogFileInit(const std::string &moduleName, const std::string &basePath,
                  LoggerImp::LLogLevelType level, bool bDispConsole = false);
void WQLogFileRelease();
size_t WQLogFilePush(WQLogFileItem &&item);



#define LOG_TRACE_ASYN          LogAsync    ( LoggerImp::LLogLevelType::TRACE,      LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL)) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE) )
#define LOG_DEBUG_ASYN          LogAsync    ( LoggerImp::LLogLevelType::DEBUG,      LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL)) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE) )
#define LOG_INFO_ASYN           LogAsync    ( LoggerImp::LLogLevelType::INFO,       LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL)) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE) )
#define LOG_WARN_ASYN           LogAsync    ( LoggerImp::LLogLevelType::WARN,       LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL)) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE) )
#define LOG_ERROR_ASYN          LogAsync    ( LoggerImp::LLogLevelType::ERROR,      LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL)) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE) )
#define LOG_FATAL_ASYN          LogAsync    ( LoggerImp::LLogLevelType::FATAL,      LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL)) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE) )



#define LOG_TRACE_OBJ_ASYN(que) LoggerImpWQ ( &(que), LoggerImp::LLogLevelType::TRACE,     LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL)) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE) )
#define LOG_DEBUG_OBJ_ASYN(que) LoggerImpWQ ( &(que), LoggerImp::LLogLevelType::DEBUG,     LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL)) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE) )
#define LOG_INFO_OBJ_ASYN(que)  LoggerImpWQ ( &(que), LoggerImp::LLogLevelType::INFO,      LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL)) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE) )
#define LOG_WARN_OBJ_ASYN(que)  LoggerImpWQ ( &(que), LoggerImp::LLogLevelType::WARN,      LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL)) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE) )
#define LOG_ERROR_OBJ_ASYN(que) LoggerImpWQ ( &(que), LoggerImp::LLogLevelType::ERROR,     LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL)) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE) )
#define LOG_FATAL_OBJ_ASYN(que) LoggerImpWQ ( &(que), LoggerImp::LLogLevelType::FATAL,     LLogMsg (__FILE__, __LINE__, __func__), (static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ALL)) & ~static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::DISP_CONSOLE) )

#define LOG_TRACE_O             LOG_TRACE_OBJ_ASYN
#define LOG_DEBUG_O             LOG_DEBUG_OBJ_ASYN
#define LOG_INFO_O              LOG_INFO_OBJ_ASYN
#define LOG_WARN_O              LOG_WARN_OBJ_ASYN
#define LOG_ERROR_O             LOG_ERROR_OBJ_ASYN
#define LOG_FATAL_O             LOG_FATAL_OBJ_ASYN


/**
 * Brief : Worker Queue for Log File
 *
*/

class WQLogFile
    : public WorkQueue<WQLogFileItem, Thread>
    , public LLogFile
{
    public  :
        int     Pop(WQLogFileItem *pData);
        int     Init(WQ_QUEUE_STATE state, const std::string &moduleName, const std::string &path);
        int     Init(WQ_QUEUE_STATE state, const std::string &moduleName, const std::string &path, bool bDispConsole);

    private :
        bool    _bDispConsole = false;

};


/**
 *
 *
*/

class LoggerImpWQ : public LoggerImp
{
    public :
        LoggerImpWQ(WQLogFile *que,
                    LoggerImp::LLogLevelType type,
                    const std::string &msg,
                    LoggerImp::flag_t flags)
            : LoggerImp(type, msg, flags)
            , _que(que)
        {
            if (nullptr == que)
                std::cerr << "ERROR : Unable to create a log file. Invalid WQLogFile pointer." << std::endl;
        }

        ~LoggerImpWQ()
        {
            if (_que)
                _que->PushBack( {LoggerImp::_logLevel, LogText()} );
            else
                std::cerr << "ERROR : Unable to create a log file. Invalid WQLogFile pointer." << std::endl;
        }

    private:
        WQLogFile *_que;
};


/**
 *
 *
*/

class LogAsync : public LoggerImp
{
    public:
        LogAsync(LoggerImp::LLogLevelType type, const std::string &msg, LoggerImp::flag_t flags)
            : LoggerImp(type, msg, flags)
        {
        }

        ~LogAsync()
        {
            WQLogFilePush( {LoggerImp::_logLevel, LogText()} );
        }
};



#endif //__LIGHT_LOGGER_FILE_ASYNC_HPP__

// clang-format on

