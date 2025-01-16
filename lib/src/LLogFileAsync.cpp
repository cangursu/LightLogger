
// clang-format off

#include "LLogFileAsync.hpp"
#include "LLogImp.h"

static WQLogFile s_queueLog;


int WQLogFileInit(const std::string &moduleName, const std::string &basePath, LoggerImp::LLogLevelType level, bool bDispConsole)
{
    LoggerImp::LLogLevel(level);
    return s_queueLog.Init(WQ_QUEUE_STATE::WORKING, moduleName, basePath, bDispConsole);
}


void WQLogFileRelease()
{
    std::cout << "Stopping Logging and waiting to consume the rest.\n";
    s_queueLog.Release();
}


size_t WQLogFilePush(WQLogFileItem &&item)
{
    return s_queueLog.PushBack(std::move(item));
}


int WQLogFile::Pop(WQLogFileItem *pData)
{
    if (LoggerImp::LLogDo(pData->_type))
        FileWrite(pData->_txt);

    if (_bDispConsole && (LoggerImp::LLogDoConsole(pData->_type)))
        std::cout << pData->_txt;
    return 0;
}


int WQLogFile::Init(WQ_QUEUE_STATE state, const std::string &moduleName, const std::string &path, bool bDispConsole)
{
    _bDispConsole = bDispConsole;
    if (-1 == LLogFile::Init(moduleName, path))
        return -1;
    return WorkQueue::Init(state, moduleName);
}


int WQLogFile::Init(WQ_QUEUE_STATE state, const std::string &moduleName, const std::string &path)
{
    return WQLogFile::Init(state, moduleName, path, false);
}


// clang-format on
