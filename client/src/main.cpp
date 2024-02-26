
#include "LLog.h"

#include <iostream>
#include <bitset>



int main(int argc, const char * argv[])
{
    std::cout << "LigthLogger Usage sample project." <<  std::endl;

    LoggerImp::LLogLevel(LoggerImp::LLogLevelType::TRACE);

    LOG_TRACE << "Loging is beautiful";
    LOG_INFO  << "For Your Information";
    LOG_ERROR << "But not every time";

    return 0;
}
