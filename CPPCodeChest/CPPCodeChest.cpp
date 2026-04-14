// CPPCodeChest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING


#include <iostream>
#include <chrono>

#include "src/common/utils.h"
#include "src/common/logger.h"
#include "src/common/mysqlDB.h"
#include "src/common/parseYamlFile.h"
#include "src/thread/threadPool.h"
#include "src/thread/threadPool.hpp"


#include "src/cplusplus/CPP_FUNC_API.h"

#include <iostream>
 

int main() {
    ThreadPool mypool(4);

    for (rsize_t i = 0; i < 20; i++) {
   	 auto rsfuture0 = mypool.enques([](int a, int b)->int {
   		 std::cout << "当前线程： " << std::this_thread::get_id() << std::endl;
   		 return a + b; }, 10 * i, 10 * i);
   	 std::cout << "thread rs:" << rsfuture0.get() << std::endl;
    }
}

//
//int main()
//{
//
//	Logger logger;
//	logger.writeLog("Starting the application...", Logger::LoggerType::INFO);
//
//
//    
//    //// 获取当前时间点
//    //auto start = std::chrono::high_resolution_clock::now();
//
//
//    //    // 创建多个线程
//    //    std::vector<std::thread> threads;
//    //    for (int i = 0; i < 10; ++i) {
//    //        threads.emplace_back(incrementCounter, i);
//    //    }
//
//    //    // 等待所有线程完成
//    //    for (auto& t : threads) {
//    //        t.join();
//    //    }
//
//    //    // 输出最终的共享计数器值
//    //    std::cout << "Final value of sharedCounter: " << sharedCounter << std::endl;
//
//    //// 获取当前时间点
//    //auto end = std::chrono::high_resolution_clock::now();
//
//    //// 计算时间差
//    //std::chrono::duration<double> duration = end - start;
//    //std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
//
//}


