
#include "LLogFileAsync.hpp"


void MainLogFile()
{
    std::cout << __func__ << ":" << __LINE__ << " --->\n";
    WQLogFileInit("QueueLogTest", "./logs", LoggerImp::LLogLevelType::TRACE, true);

    LOG_TRACE_ASYN << "Starting Logigng";
    size_t i;
    for (i = 0; i < 1000/*1000000*/; ++i)
        LOG_TRACE_ASYN << "Loging is beautiful - " << i << ".";

    std::cout << __func__ << ":" << __LINE__ << " i : " << i << "\n";

    LOG_INFO_ASYN << "For Your Information";
    LOG_ERROR_ASYN << "But not every time";

    WQLogFileRelease();
    std::cout << __func__ << ":" << __LINE__ << " ---<\n";
}


void MainLogFileMulti()
{
    LoggerImp::LLogLevel(LoggerImp::LLogLevelType::TRACE);

    WQLogFile wqLog1;
    WQLogFile wqLog2;

    wqLog1.Init(WQ_QUEUE_STATE::WORKING, "MLogBasic1", "./logs", true);
    wqLog2.Init(WQ_QUEUE_STATE::WORKING, "MLogBasic2", "./logs", true);

    LOG_WARN_O(wqLog1)  << "Sample of Multiple Simultaneous Logging for LOG 1";
    LOG_TRACE_O(wqLog2) << "Sample of Multiple Simultaneous Logging for LOG 2";

    wqLog1.Release();
    wqLog2.Release();
}


void MainLogMultipleStress()
{
    constexpr int countTh = 50;
    constexpr int maxLine = 1000;//100000;
    std::thread th[countTh];
    for (int i = 0; i < countTh; ++i)
    {
        th[i] = std::thread (
            [] (int idx, int maxLine) -> void {
                WQLogFile wqLog;
                if (0 != wqLog.Init(WQ_QUEUE_STATE::WORKING, "wqLog" + std::to_string(idx), "./logs/multiple"/*, true*/) )
                {
                    std::cerr << "ERROR : WQLogFile::Init failed\n";
                    return;
                }

                for (int iLine = 0; iLine < maxLine; ++iLine)
                    LOG_FATAL_O(wqLog) << "IDX : " << idx << " - Stress Logging LINE : " << iLine;

                wqLog.Release();
            }
            , i, maxLine  );
    }

    for (int i = 0; i < countTh; ++i)
        if (th[i].joinable()) th[i].join();
}
