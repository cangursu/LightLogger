
#include "LLog.h"

#include <iostream>
#include <bitset>



int main(int argc, const char * argv[])
{
    std::cout << "Hello  " <<  std::endl;

    LoggerImp::LLogLevel(LoggerImp::LLogLevelType::DEBUG);

    LLOG_TRACE << "Loging is beautiful";
    LLOG_INFO << "For Your Information";
    LLOG_ERROR << "But not every time";

    return 0;
}
