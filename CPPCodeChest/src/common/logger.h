#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <ctime>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#endif

// 使用单例模式构造

// 避免宏冲突
#ifdef DEBUG
#undef DEBUG
#endif
#ifdef ERROR
#undef ERROR
#endif

enum class LogLevel {
    Debug = 0,
    Info = 1,
    Warn = 2,
    Error = 3,
    None = 4
};

class Logger {
public:
    static Logger& getInstance();

    void setLevel(LogLevel level);
    void setLogFile(const std::string& filePath);
    void setConsoleOutput(bool enable);
    void setLogName(const std::string& name);  // 设置日志名称，如 [VisionLog]

    void setLogPath(const std::string& path);  // 设置日志文件夹路径
    void createDirectory(const std::string& path);  // 创建目录
    std::string generateLogFileName();  // 生成日志文件名

    // 日志输出接口
    void debug(const std::string& message);
    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);

    // 流式输出
    class LogStream {
    public:
        LogStream(Logger& logger, LogLevel level);
        ~LogStream();

        template<typename T>
        LogStream& operator<<(const T& value) {
            m_stream << value;
            return *this;
        }

    private:
        Logger& m_logger;
        LogLevel m_level;
        std::ostringstream m_stream;
    };

    LogStream debug();
    LogStream info();
    LogStream warn();
    LogStream error();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger();
    ~Logger();

    void write(LogLevel level, const std::string& message);
    int getThreadId();           // 获取线程ID
    std::string getCurrentTime();
    std::string levelToString(LogLevel level);

private:
    std::ofstream m_fileStream;
    std::mutex m_mutex;
    LogLevel m_level;
    bool m_consoleOutput;
    std::string m_logFilePath;
    std::string m_logName;       // 日志名称，如 [VisionLog]
};

// 宏定义
#define LOG_DEBUG(msg) Logger::getInstance().debug(msg)
#define LOG_INFO(msg)  Logger::getInstance().info(msg)
#define LOG_WARN(msg)  Logger::getInstance().warn(msg)
#define LOG_ERROR(msg) Logger::getInstance().error(msg)

#define LOG_DEBUG_STREAM Logger::getInstance().debug()
#define LOG_INFO_STREAM  Logger::getInstance().info()
#define LOG_WARN_STREAM  Logger::getInstance().warn()
#define LOG_ERROR_STREAM Logger::getInstance().error()


// ======================================== 用法 =====================================
///
/// #include "Logger.h"
//
//int main() {
//    Logger& logger = Logger::getInstance();
//
//    // 方式1：设置日志文件夹路径（自动创建文件夹和带时间戳的文件名）
//    logger.setLogPath("./Logs");  // 会在 ./Logs 文件夹创建 VisionLog2025-12-17_09-17-17_199.log
//
//    // 方式2：设置完整的文件路径
//    // logger.setLogFile("./Logs/VisionLog2025-12-17_09-17-17_199.log");
//
//    // 配置其他选项
//    logger.setLevel(LogLevel::Debug);
//    logger.setConsoleOutput(true);
//    logger.setLogName("[VisionLog]");
//
//    // 写入日志
//    logger.info("设置mtp日志输出OK!");
//    logger.debug("This is debug message");
//    logger.error("Error occurred");
//
//    return 0;
//}
///