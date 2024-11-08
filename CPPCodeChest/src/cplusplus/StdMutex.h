#pragma once
/***
* 
* 
* 互斥所是多线程编程中的一种重要同步机制，用于保护共享资源，防止数据竞争和竞态条件。通过使用std::mutex和std::lock_guard,可以有效的管理和保护共享资源，确保多线程程序的正确性和安全性。
* 
* 作用：保护共享资源，防止数据竞争，确保线程安全
* 
* 基本用法：
* 
*  std::metux mtx；
*   
*   1、自动管理内存
*  	std::lock_guard<std::mutex> lock(mtx);    // 1、自动管理内存
*   
*   2：使用lock() 和 unlock(),中间加入需要保护的变量
* 	    //mtx.lock();
		++sharedCounter;
		//mtx.unlock();
* 
***/

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>



// 共享资源
int sharedCounter = 0;

// 互斥锁
std::mutex mtx;

// 线程函数
void incrementCounter(int id) {
	for (int i = 0; i < 1000000; ++i) {
		// 锁定互斥锁
		mtx.lock();
		// std::lock_guard<std::mutex> lock(mtx);
		++sharedCounter;
		mtx.unlock();
	}

	std::cout << "Thread " << id << " finished." << std::endl;
}

//int main() {
//    // 创建多个线程
//    std::vector<std::thread> threads;
//    for (int i = 0; i < 10; ++i) {
//        threads.emplace_back(incrementCounter, i);
//    }
//
//    // 等待所有线程完成
//    for (auto& t : threads) {
//        t.join();
//    }
//
//    // 输出最终的共享计数器值
//    std::cout << "Final value of sharedCounter: " << sharedCounter << std::endl;
//
//    return 0;
//}