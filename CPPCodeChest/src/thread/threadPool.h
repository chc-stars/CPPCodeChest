#pragma once
// 摘录：
// https://blog.csdn.net/qingyangwuji/article/details/130305045?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefau
// lt%7ECTRLIST%7EPaidSort-1-130305045-blog-130979755.235%5Ev43%5Epc_blog_bottom_relevance_base9&depth_1-utm_source=distribute.pc_relevant_t0.
// none-task-blog-2%7Edefault%7ECTRLIST%7EPaidSort-1-130305045-blog-130979755.235%5Ev43%5Epc_blog_bottom_relevance_base9&utm_relevant_index=1

/*
	在一个线程中，如果我们需要多次使用线程，这就意味着，需要多次的创建并销毁线程。而创建并销毁线程的过程势必会消耗内存，	
	线程过多会带来调动的开销，进而影响缓存局部性和整体性能。

	线程的创建和销毁有以下缺点：

	创建太多线程，将浪费一定资源，有些线程未被充分使用。
	销毁太多线程，将导致之后浪费时间再次创建他们。
	创建线程太慢， 将会导致长时间的等待，性能变差。

	线程池维护者多个线程，这避免了在处理短时间任务时，创建与销毁线程的代价。

    * 在程序开始运行前创建多个线程，这样，程序在运行时，只需要从线程池中拿来用就可以了， 大大提高了程序运行的效率。
	* 一般线程池都会有以下几个部分构成：
	* 1、线程池管理器（ThreadPoolManage）：用于创建并管理线程池，也就是线程池类
	* 2、工作线程（workThread）：线程池中线程
	* 3、任务队列task：用于存放没有处理的任务。提供一种缓冲机制。
	* 4、append：用于添加任务的接口
	* 
*/

/*
说明：

构造函数创建所需要的线程数

一个线程对应一个任务，任务随时可能完成，线程则可能休眠，所以任务用队列queue实现（线程数量有限），线程用采用wait机制。

任务在不断的添加，有可能大于线程数，处于队首的任务先执行。

只有添加任务(append)后，才开启线程condition.notify_one()。

wait表示，任务为空时，则线程休眠，等待新任务的加入。

添加任务时需要添加锁，因为共享资源。
*/

#ifndef THREADPOOL_H
#define THREADPOOL_H


#include <vector>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <stdexcept>
#include <condition_variable>
#include <memory>  // unique_ptr
#include <assert.h>


const int MAX_THREADS = 1000;       // 最大线程数



template <typename T>
class threadPool
{
public:
	threadPool(int number = 1);   // 默认只开一个线程
	~threadPool();

	std::queue<T *> tasks_queue;  // 任务队列
	
	bool append(T *request);  // 向请求队列<tasks_queue>中添加任务 <T>



private:
	// 工作线程需要运行的函数，不断的从任务队列中取出来执行
	static void worker(void *arg);  

	void run();

private:

	std::vector<std::thread> work_threads;   // 工作线程

	std::mutex queue_mutex;
	std::condition_variable condition;  // 必须与unique_lock配合使用
	bool stop;

};


#endif

// 测试代码


#include<string>
#include<math.h>
using namespace std;
class Task
{
public:
	void process()
	{
		//cout << "run........." << endl;//测试任务数量
		long i = 100;
		while (i != 0)
		{
			int j = sqrt(i);
			i--;
		}
	}
};

int runThreadPool();

