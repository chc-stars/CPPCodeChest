#pragma once
// ժ¼��
// https://blog.csdn.net/qingyangwuji/article/details/130305045?spm=1001.2101.3001.6661.1&utm_medium=distribute.pc_relevant_t0.none-task-blog-2%7Edefau
// lt%7ECTRLIST%7EPaidSort-1-130305045-blog-130979755.235%5Ev43%5Epc_blog_bottom_relevance_base9&depth_1-utm_source=distribute.pc_relevant_t0.
// none-task-blog-2%7Edefault%7ECTRLIST%7EPaidSort-1-130305045-blog-130979755.235%5Ev43%5Epc_blog_bottom_relevance_base9&utm_relevant_index=1

/*
	��һ���߳��У����������Ҫ���ʹ���̣߳������ζ�ţ���Ҫ��εĴ����������̡߳��������������̵߳Ĺ����Ʊػ������ڴ棬	
	�̹߳������������Ŀ���������Ӱ�컺��ֲ��Ժ��������ܡ�

	�̵߳Ĵ���������������ȱ�㣺

	����̫���̣߳����˷�һ����Դ����Щ�߳�δ�����ʹ�á�
	����̫���̣߳�������֮���˷�ʱ���ٴδ������ǡ�
	�����߳�̫���� ���ᵼ�³�ʱ��ĵȴ������ܱ�

	�̳߳�ά���߶���̣߳���������ڴ����ʱ������ʱ�������������̵߳Ĵ��ۡ�

    * �ڳ���ʼ����ǰ��������̣߳�����������������ʱ��ֻ��Ҫ���̳߳��������þͿ����ˣ� �������˳������е�Ч�ʡ�
	* һ���̳߳ض��������¼������ֹ��ɣ�
	* 1���̳߳ع�������ThreadPoolManage�������ڴ����������̳߳أ�Ҳ�����̳߳���
	* 2�������̣߳�workThread�����̳߳����߳�
	* 3���������task�����ڴ��û�д���������ṩһ�ֻ�����ơ�
	* 4��append�������������Ľӿ�
	* 
*/

/*
˵����

���캯����������Ҫ���߳���

һ���̶߳�Ӧһ������������ʱ������ɣ��߳���������ߣ����������ö���queueʵ�֣��߳��������ޣ����߳��ò���wait���ơ�

�����ڲ��ϵ���ӣ��п��ܴ����߳��������ڶ��׵�������ִ�С�

ֻ���������(append)�󣬲ſ����߳�condition.notify_one()��

wait��ʾ������Ϊ��ʱ�����߳����ߣ��ȴ�������ļ��롣

�������ʱ��Ҫ���������Ϊ������Դ��
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


const int MAX_THREADS = 1000;       // ����߳���



template <typename T>
class threadPool
{
public:
	threadPool(int number = 1);   // Ĭ��ֻ��һ���߳�
	~threadPool();

	std::queue<T *> tasks_queue;  // �������
	
	bool append(T *request);  // ���������<tasks_queue>��������� <T>



private:
	// �����߳���Ҫ���еĺ��������ϵĴ����������ȡ����ִ��
	static void worker(void *arg);  

	void run();

private:

	std::vector<std::thread> work_threads;   // �����߳�

	std::mutex queue_mutex;
	std::condition_variable condition;  // ������unique_lock���ʹ��
	bool stop;

};


#endif

// ���Դ���


#include<string>
#include<math.h>
using namespace std;
class Task
{
public:
	void process()
	{
		//cout << "run........." << endl;//������������
		long i = 100;
		while (i != 0)
		{
			int j = sqrt(i);
			i--;
		}
	}
};

int runThreadPool();

