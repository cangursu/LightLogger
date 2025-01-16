
#include "LLog.h"

#include <iostream>
#include <bitset>


void MainLog();

void MainLogFile();
void MainLogFileMulti();
void MainLogMultipleStress();


int main(int argc, const char * argv[])
{
    std::cout << "LigthLogger Usage sample project. v2.0" <<  std::endl;

    LoggerImp::LLogLevel(LoggerImp::LLogLevelType::TRACE);

//    MainLog();
//    MainLogFile();
//    MainLogFileMulti();
    MainLogMultipleStress();

    return 0;
}


void MainLog()
{
    LOG_TRACE << "Loging is beautiful";
    LOG_INFO  << "For Your Information";
    LOG_ERROR << "But not every time";
}
