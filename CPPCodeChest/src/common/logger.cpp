#include "logger.h"

namespace fs = std::filesystem;  // 简化命名空间

Logger::Logger()
    : logFile(createLogFileName(), std::ios::out | std::ios::app) {
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::stringstream ss;
    ss << "********************************************" << "\n";
    logFile << ss.str();
}

Logger::~Logger() {
    logFile.close();
}

void Logger::writeLog(const std::string& message, LoggerType logType) {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::stringstream ss;

    switch (logType)
    {
        case LoggerType::INFO:
            ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " [INFO]: "  << message << "\n";
            break;
        case LoggerType::WARNING:
            ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " [WARNING]: " << message << "\n";
            break;
        case LoggerType::DEBUG:
            ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " [DEBUG]: " << message << "\n";
            break;
        case LoggerType::ERROR:
            ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " [ERROR]: " << message << "\n";
            break;
        case LoggerType::FATAL:
            ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " [FATAL]: " << message << "\n";
            break;
        case LoggerType::PERFORMANCE:
            ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " [PERFORMANCE]: " << message << "\n";
            break;
        case LoggerType::SECURITY:
            ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " [SECURITY]: " << message << "\n";
            break;
        default:
            ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "[INFO]: " << message << "\n";
            break;
    }

    logFile << ss.str();

}


std::string Logger::createLogFileName() {
    
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // 定义Log文件夹路径（运行目录下的Log文件夹）

    std::stringstream ss;
    const std::string logDir = "Log";
    try {
        fs::create_directories(logDir);
        ss << std::put_time(std::localtime(&in_time_t), "./Log/log_%Y-%m-%d_%H.log");

    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "创建Log文件夹失败,文件存放于运行根目录下：" << e.what() << std::endl;
        ss << std::put_time(std::localtime(&in_time_t), "/log_%Y-%m-%d_%H.log");

    }

    return ss.str();
}
