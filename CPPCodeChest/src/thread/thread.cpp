#include "thread.h"

#include <iostream>


void thread_1()
{
    std::cout << "子线程1" << std::endl;
}


void thread_2(int x)
{
    std::cout << "x:" << x << std::endl <<  x << "\n";
    std::cout << "子线程2" << std::endl;
}


int runThread()
{
    std::thread first(thread_1); // 开启线程，调用：thread_1()
    std::thread second(thread_2, 100); // 开启线程，调用：thread_2(100)
    //thread third(thread_2,3);//开启第3个线程，共享thread_2函数。
    std::cout << "主线程\n";


    first.join(); //必须说明添加线程的方式            
    second.join();
    std::cout << "子线程结束.\n";//必须join完成
    return 0;
}