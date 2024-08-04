#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>

// C++: 日志函数.

class Logger {
public:
    Logger();
    ~Logger();

    enum LoggerType  // 消息类型
    {
        INFO,    // 一般信息
        WARNING, // 警告
        DEBUG,   // 用于调试信息，通常在开发阶段使用，包含详细的程序流程和状态信息，帮助开发者定位问题。
        ERROR,   // 用于记录错误信息，当程序发生错误或异常时使用
        FATAL,   // 用于记录严重的错误，可能导致程序崩溃或停止运行的情况。
        PERFORMANCE,   // 用于记录性能指标，如CPU使用率、内存使用情况等，帮助优化程序性能。
        SECURITY,      // 用于记录与安全相关的事件，如登录尝试、权限访问等。

    };


    void writeLog(const std::string& message, LoggerType logType = LoggerType::INFO);  // 写入，

private:
    std::ofstream logFile;
    std::string createLogFileName();
};

// ************************************** 用例 ***********************************

//int main() {
//    Logger logger;
//
//    logger.writeLog("This is a log message.");
//    logger.writeLog("Another log message.");
//
//    return 0;
//}