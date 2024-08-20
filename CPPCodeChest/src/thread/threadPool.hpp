#pragma

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
#include <queue>

/// <summary>
/// 线程池
/// <summary>


class  ThreadPool
{
public:
	 ThreadPool(int threadnums);

	~ ThreadPool();

	// 添加任务到队列
	template <typename F, typename ...Arg>
	auto enques(F&& f, Arg&&... arg) ->std::future<typename std::result_of<F(Arg...)>::type>;
	
private:
	void worker();  // 线程的执行内容
	bool isstop;    // 标识 当前线程池是不是停止 true停止
	std::condition_variable cv;   // 条件变量
	std::mutex mtx;      // 互斥锁
	std::vector<std::thread>  workers;  // 线程集合 （线程池）
	std::queue<std::function<void()>> myque;   // 任务队列


};

 ThreadPool:: ThreadPool(int threadnums) :isstop(false)
{
	 for (rsize_t i = 0; i < threadnums; i++) {
		 workers.emplace_back([this]() {
			this->worker();
			});
	 }
}

 ThreadPool::~ ThreadPool()
{
	 // 更改停止标识
	{
		std::unique_lock<std::mutex>(mtx);
		isstop = true;
	}

	// 通知所有阻塞中的线程
	cv.notify_all();

	// 确保线程执行完毕
	for (std::thread& onethread : workers) {
		onethread.join();
	}

}

 //添加任务
 template <typename F, typename ...Arg>
 auto ThreadPool::enques(F&& f, Arg&&... arg)->std::future<typename std::result_of<F(Arg...)>::type>
 {
	 // 获得f执行后的类型
	 using functype = typename std::result_of<F(Arg...)>::type;

	 // 获得一个智能指针 直线一个被包装为functype（）的task
	 auto task = std::make_shared<std::packaged_task<functype()>>(
		 std::bind(std::forward<F>(f), std::forward<Arg>(arg)...)
		 );

	 // 获得future

	 std::future<functype> rsfuture = task->get_future();

	 // 将任务添加到队列
	 {
		 std::lock_guard<std::mutex> lockguard(this->mtx);
		 if (isstop)
			 throw std::runtime_error("出错： 线程池已经停止了");

		 // 将任务添加到队列
		 myque.emplace([task]() {
			 (*task)();
		 });
	 }

	 // 通知线程去执行任务
	 cv.notify_one();

	 // 返回future
	 return rsfuture;
 }


 void ThreadPool::worker() {

	 while (true)
	 {
		// 定义任务
		 std::function<void()> task;

		 // 重队列中取得一个任务
		 {
			 std::unique_lock<std::mutex>lock(mtx);
			 cv.wait(lock, [this] { return this->isstop || !this->myque.empty(); });
			 
			 if (isstop && myque.empty()) return;
			 task = std::move(this->myque.front());
			 this->myque.pop();
				 
	 
		 }
		 // 执行任务
		 task();
	 }

 }


 // ************************************** 用例 ***********************************
 // include <iostream>
 // include "threadPool.hpp"
 // 

 //int main() {
	// ThreadPool mypool(4);

	// for (rsize_t i = 0; i < 20; i++) {
	//	 auto rsfuture0 = mypool.enques([](int a, int b)->int {
	//		 std::cout << "当前线程： " << std::this_thread::get_id() << std::endl;
	//		 return a + b; }, 10 * i, 10 * i);
	//	 std::cout << "thread rs:" << rsfuture0.get() << std::endl;
	// }
 //}

 // 若c++ 为17 则在调用的文件中加入  #define _SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING  屏蔽警告