#include "thread.h"

#include <iostream>


void thread_1()
{
    std::cout << "���߳�1" << std::endl;
}


void thread_2(int x)
{
    std::cout << "x:" << x << std::endl <<  x << "\n";
    std::cout << "���߳�2" << std::endl;
}


int runThread()
{
    std::thread first(thread_1); // �����̣߳����ã�thread_1()
    std::thread second(thread_2, 100); // �����̣߳����ã�thread_2(100)
    //thread third(thread_2,3);//������3���̣߳�����thread_2������
    std::cout << "���߳�\n";


    first.join(); //����˵������̵߳ķ�ʽ            
    second.join();
    std::cout << "���߳̽���.\n";//����join���
    return 0;
}