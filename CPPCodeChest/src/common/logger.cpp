#include "Logger.h"
#include <sys/stat.h>

#ifdef  _WIN32
#include <direct.h>
#else
#include <sys/stat.h>  
#endif //  _WIN32



Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::Logger()
    : m_level(LogLevel::Debug)
    , m_consoleOutput(true)
    , m_logName("") {
    m_logFilePath = "log.txt";
    m_fileStream.open(m_logFilePath, std::ios::out | std::ios::app);
}

Logger::~Logger() {
    if (m_fileStream.is_open()) {
        m_fileStream.close();
    }
}

void Logger::setLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_level = level;
}

void Logger::setConsoleOutput(bool enable) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_consoleOutput = enable;
}

void Logger::setLogName(const std::string& name) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_logName = name;
}

void Logger::setLogPath(const std::string& path)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    createDirectory(path);

    m_logFilePath = path + "/" + generateLogFileName();

    if (m_fileStream.is_open()) {
        m_fileStream.close();
    }

    m_fileStream.open(m_logFilePath, std::ios::out | std::ios::app);
    if (!m_fileStream.is_open()) {
        std::cerr << "Failed to open log file: " << m_logFilePath << std::endl;
    }

}

void Logger::createDirectory(const std::string& path) {
#ifdef _WIN32
    if (_mkdir(path.c_str()) == 0 || errno == EEXIST) {
        // 目录创建成功或已存在
    }
#else
    if (mkdir(path.c_str(), 0755) == 0 || errno == EEXIST) {
        // 目录创建成功或已存在
    }
#endif
}


std::string Logger::generateLogFileName() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &time_t);
#else
    localtime_r(&time_t, &tm);
#endif

    std::ostringstream oss;
    oss << "VisionLog"
        << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S")  // 注意：这里用 - 而不是 _ 避免 Windows 文件名问题
        << "_" << std::setfill('0') << std::setw(3) << ms.count()
        << ".log";

    return oss.str();
}

void Logger::setLogFile(const std::string& filePath) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_fileStream.is_open()) {
        m_fileStream.close();
    }

    m_logFilePath = filePath;
    m_fileStream.open(m_logFilePath, std::ios::out | std::ios::app);
}

int Logger::getThreadId() {
#ifdef _WIN32
    return GetCurrentThreadId();
#else
    return std::hash<std::thread::id>{}(std::this_thread::get_id());
#endif
}

std::string Logger::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &time_t);
#else
    localtime_r(&time_t, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
        << "." << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
    case LogLevel::Debug: return "DEBUG";
    case LogLevel::Info:  return "INFO";
    case LogLevel::Warn:  return "WARN";
    case LogLevel::Error: return "ERROR";
    default:              return "UNKN";
    }
}

void Logger::write(LogLevel level, const std::string& message) {
    if (level < m_level) {
        return;
    }

    std::lock_guard<std::mutex> lock(m_mutex);

    // 格式：[线程ID] 时间 [级别]: 消息[日志名称]
    // 示例：[46108] 2026-04-12 12:19:37.774 [INFO]: 设置mtp日志输出OK![VisionLog]
    std::ostringstream formatted;
    formatted << "[" << getThreadId() << "] "
        << getCurrentTime() << " ["
        << levelToString(level) << "]: "
        << message;

    // 如果有日志名称，追加到末尾
    if (!m_logName.empty()) {
        formatted << m_logName;
    }

    std::string output = formatted.str();

    // 写入文件
    if (m_fileStream.is_open()) {
        m_fileStream << output << std::endl;
        m_fileStream.flush();
    }

    // 输出到控制台
    if (m_consoleOutput) {
        if (level == LogLevel::Error) {
            std::cerr << output << std::endl;
        }
        else {
            std::cout << output << std::endl;
        }
    }
}

void Logger::debug(const std::string& message) {
    write(LogLevel::Debug, message);
}

void Logger::info(const std::string& message) {
    write(LogLevel::Info, message);
}

void Logger::warn(const std::string& message) {
    write(LogLevel::Warn, message);
}

void Logger::error(const std::string& message) {
    write(LogLevel::Error, message);
}

Logger::LogStream::LogStream(Logger& logger, LogLevel level)
    : m_logger(logger), m_level(level) {
}

Logger::LogStream::~LogStream() {
    m_logger.write(m_level, m_stream.str());
}

Logger::LogStream Logger::debug() {
    return LogStream(*this, LogLevel::Debug);
}

Logger::LogStream Logger::info() {
    return LogStream(*this, LogLevel::Info);
}

Logger::LogStream Logger::warn() {
    return LogStream(*this, LogLevel::Warn);
}

Logger::LogStream Logger::error() {
    return LogStream(*this, LogLevel::Error);
}