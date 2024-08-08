#pragma once

//摘录：https://blog.csdn.net/liang19890820/article/details/130979755?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0-130979755-blog-137497800.235^v43^pc_blog_bottom_relevance_base9&spm=1001.2101.3001.4242.1&utm_relevant_index=1

// ***************************
// 1、 多线程与多进程
// 多进程并发是将一个应用程序划分为多个独立的进程（每个进程只有一个线程），这些独立的进程间可以互相通信，共同完成任务。
// 多线程并发指的是在同一个进程中执行多个线程
// 同一进程中的多个线程共享相同的地址空间，可以访问进程中的大部分数据，
//		- 指针和引用可以在线程间进行传递。这样，同一进程内的多个线程能够很方便的进行数据共享以及通信，也就比进程更适用于并发操作。


// 创建线程

// 形式1
/*

	void thread_func() {}   // 线程函数
	std::thread mythread(thread_func);  // 函数形式为 void thread_fun()
	mythread.join();         //同一个函数可以代码复用，创建多个线程

	// 形式2
	void thread_func2(int x) {}
	std::thread mythread2(thread_func2(100));
	mythread2.join();
	//函数形式为void thread_fun(int x)
	//同一个函数可以代码复用，创建多个线程

	// 形式3
	std::thread(thread_func, 1).detach();  // 直接创建线程， 没有名字。  函数形式为void thread_func(int x)

	1.4 join与detach

	当线程启动后，一定要在和线程相关联的thread销毁前，确定以何种方式等待线程执行结束。
		·detach方式，启动的线程自主在后台运行，当前的代码继续向下执行，不等待新线程借宿。
		·join方式，等待启动的线程完成，才会继续向下执行。
	可以通过joinable判断是join模式还是detach模式。

	eg：
		if (myThread.joinable()) 
			foo.join();

*/

#include <thread>
void thread_2(int x);
void thread_1();
int runThread();


// 2.1 lock与unlock
/*
lock()： 资源上锁
unlock():  解锁资源
trylock():  查看是否上锁： 情况有3种：1） 未上锁，返回false, 并锁住； 2）其他线程已上锁，返回true； 3）同一个线程已经对他上锁，产生死锁。
	死锁：指的是两个或者以上的进程，由于竞争资源或者彼此通信而造成的一种阻塞现象，若无外力作用，他们将无法推进下去，导致系统处于死锁状态，永远在互相等待的进程成为死锁进程。

同一个mutex变量上锁之后，一段时间内，只允许一个线程访问它。

#include// std::cout
#include// std::thread
#include// std::mutex


std::mutex mtx;  // mutex for critical section
void print_block (int n, char c)
{
// critical section (exclusive access to std::cout signaled by locking mtx):
	mtx.lock();
	for (int i=0; i
	{
	   std::cout << c;
	}
	std::cout << '\n';
	mtx.unlock();
}
int main ()
{
	std::thread th1 (print_block,50,'');//线程1：打印*
	std::thread th2 (print_block,50,'$');//线程2：打印$

	th1.join();
	th2.join();
	return 0;
}

输出为：
	**************************************************
	$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


	如果是不同mutex变量，因为不涉及到同一资源的竞争，所以一下代码运行可能会出现交替打印的情况，或者一个线程可以修改共同的全局变量！

	#include // std::cout
#include // std::thread
#include // std::mutex


std::mutex mtx_1; // mutex for critical section
std::mutex mtx_2;  // mutex for critical section
int test_num = 1;


void print_block_1 (int n, char c)
{
// critical section (exclusive access to std::cout signaled by locking mtx):
	mtx_1.lock();
	for (int i=0; i
	{
		//std::cout << c;
		test_num = 1;
		std::cout<<test_num<<std</test_num<<::endl;
	}
		std::cout << '\n';
	mtx_1.unlock();
}


void print_block_2 (int n, char c)
{// critical section (exclusive access to std::cout signaled by locking mtx):
	mtx_2.lock();
	test_num = 2;
	for (int i=0; i
	{
	//std::cout << c;
	  test_num = 2;
	  std::cout<<test_num<<std</test_num<<::endl;
	}
	mtx_2.unlock();
}


int main ()
{
	std::thread th1 (print_block_1,10000,'*');
	std::thread th2 (print_block_2,10000,'$');


	th1.join();
	th2.join();
	return 0;
}

  2.2  lock_guard
  创建lock_guard对象时，它将尝试获取提供给它的互斥锁的所有权。当控制流离开lock_guard对象的作用域时，lock_guard析构并释放互斥量.
  
  lock_guard特点：
  创建即枷锁，作用域结束自动析构并解锁，无需手工解锁
  不能中途解锁，必须等作用域结束才解锁
  不能复制

  代码示例：
  #include
#include
#include
int g_i = 0;
std::mutex g_i_mutex;  // protects g_i，用来保护g_i


void safe_increment()
{
	const std::lock_guard<std::mutex> lock(g_i_mutex);
	++g_i;
	std::cout << std::this_thread::get_id() << ": " << g_i << '\n';// g_i_mutex自动解锁}int main(){
	std::cout << "main id: " <<std::this_thread::get_id()<<std::endl;
	std::cout << "main: " << g_i << '\n';


	std::thread t1(safe_increment);
	std::thread t2(safe_increment);


	t1.join();
	t2.join();


	std::cout << "main: " << g_i << '\n';
}

*/
