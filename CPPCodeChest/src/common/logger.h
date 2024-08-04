#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>

// C++: ��־����.

class Logger {
public:
    Logger();
    ~Logger();

    enum LoggerType  // ��Ϣ����
    {
        INFO,    // һ����Ϣ
        WARNING, // ����
        DEBUG,   // ���ڵ�����Ϣ��ͨ���ڿ����׶�ʹ�ã�������ϸ�ĳ������̺�״̬��Ϣ�����������߶�λ���⡣
        ERROR,   // ���ڼ�¼������Ϣ����������������쳣ʱʹ��
        FATAL,   // ���ڼ�¼���صĴ��󣬿��ܵ��³��������ֹͣ���е������
        PERFORMANCE,   // ���ڼ�¼����ָ�꣬��CPUʹ���ʡ��ڴ�ʹ������ȣ������Ż��������ܡ�
        SECURITY,      // ���ڼ�¼�밲ȫ��ص��¼������¼���ԡ�Ȩ�޷��ʵȡ�

    };


    void writeLog(const std::string& message, LoggerType logType = LoggerType::INFO);  // д�룬

private:
    std::ofstream logFile;
    std::string createLogFileName();
};

// ************************************** ���� ***********************************

//int main() {
//    Logger logger;
//
//    logger.writeLog("This is a log message.");
//    logger.writeLog("Another log message.");
//
//    return 0;
//}