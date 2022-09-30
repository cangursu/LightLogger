

#include "LLogImp.h"
#include <gtest/gtest.h>


TEST(LogImpl, LogFlag)
{
    LoggerImp log(LoggerImp::LLogLevelType::TRACE, static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::NONE));

    EXPECT_FALSE(log.Flag_AddLevelTag()  );
    EXPECT_FALSE(log.Flag_AddTimeStamp() );
    EXPECT_FALSE(log.Flag_AddFileLine()  );
    EXPECT_FALSE(log.Flag_AddLineFeed()  );
    EXPECT_FALSE(log.Flag_DispConsole()  );

    log.FlagSet(LoggerImp::LLogFlags::ADD_LEVEL_TAG);
    EXPECT_TRUE (log.Flag_AddLevelTag()  );
    EXPECT_FALSE(log.Flag_AddTimeStamp() );
    EXPECT_FALSE(log.Flag_AddFileLine()  );
    EXPECT_FALSE(log.Flag_AddLineFeed()  );
    EXPECT_FALSE(log.Flag_DispConsole()  );

    log.FlagSet(LoggerImp::LLogFlags::ADD_TIMESTAMP);
    EXPECT_TRUE (log.Flag_AddLevelTag()  );
    EXPECT_TRUE (log.Flag_AddTimeStamp() );
    EXPECT_FALSE(log.Flag_AddFileLine()  );
    EXPECT_FALSE(log.Flag_AddLineFeed()  );
    EXPECT_FALSE(log.Flag_DispConsole()  );

    log.FlagSet(LoggerImp::LLogFlags::ADD_FILELINE);
    EXPECT_TRUE (log.Flag_AddLevelTag()  );
    EXPECT_TRUE (log.Flag_AddTimeStamp() );
    EXPECT_TRUE (log.Flag_AddFileLine()  );
    EXPECT_FALSE(log.Flag_AddLineFeed()  );
    EXPECT_FALSE(log.Flag_DispConsole()  );

    log.FlagSet(LoggerImp::LLogFlags::ADD_LINEFEED);
    EXPECT_TRUE (log.Flag_AddLevelTag()  );
    EXPECT_TRUE (log.Flag_AddTimeStamp() );
    EXPECT_TRUE (log.Flag_AddFileLine()  );
    EXPECT_TRUE (log.Flag_AddLineFeed()  );
    EXPECT_FALSE(log.Flag_DispConsole()  );

    log.FlagSet(LoggerImp::LLogFlags::DISP_CONSOLE);
    EXPECT_TRUE (log.Flag_AddLevelTag()  );
    EXPECT_TRUE (log.Flag_AddTimeStamp() );
    EXPECT_TRUE (log.Flag_AddFileLine()  );
    EXPECT_TRUE (log.Flag_AddLineFeed()  );
    EXPECT_TRUE (log.Flag_DispConsole()  );
}

TEST(LogImpl, LogText)
{
    EXPECT_EQ(LLogMsg(__FILE__, __LINE__, __PRETTY_FUNCTION__), "main.cpp:55 (void LogImpl_LogText_Test::TestBody)");

    LoggerImp log(  LoggerImp::LLogLevelType::TRACE,
                    LLogMsg (__FILE__, __LINE__, __PRETTY_FUNCTION__),
                    static_cast<LoggerImp::flag_t>(LoggerImp::LLogFlags::ADD_LEVEL_TAG)
                 );
    log  << "Test:" << 1 << ", " << 2.1 << ", " << true;

    EXPECT_EQ(log.LogText() , "[TRACE] main.cpp:58 (void LogImpl_LogText_Test::TestBody) - Test:1, 2.1, 1");
    log.FlagReset(LoggerImp::LLogFlags::DISP_CONSOLE);

}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

