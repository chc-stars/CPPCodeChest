#pragma once

//ժ¼��https://blog.csdn.net/liang19890820/article/details/130979755?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0-130979755-blog-137497800.235^v43^pc_blog_bottom_relevance_base9&spm=1001.2101.3001.4242.1&utm_relevant_index=1

// ***************************
// 1�� ���߳�������
// ����̲����ǽ�һ��Ӧ�ó��򻮷�Ϊ��������Ľ��̣�ÿ������ֻ��һ���̣߳�����Щ�����Ľ��̼���Ի���ͨ�ţ���ͬ�������
// ���̲߳���ָ������ͬһ��������ִ�ж���߳�
// ͬһ�����еĶ���̹߳�����ͬ�ĵ�ַ�ռ䣬���Է��ʽ����еĴ󲿷����ݣ�
//		- ָ������ÿ������̼߳���д��ݡ�������ͬһ�����ڵĶ���߳��ܹ��ܷ���Ľ������ݹ����Լ�ͨ�ţ�Ҳ�ͱȽ��̸������ڲ���������


// �����߳�

// ��ʽ1
/*

	void thread_func() {}   // �̺߳���
	std::thread mythread(thread_func);  // ������ʽΪ void thread_fun()
	mythread.join();         //ͬһ���������Դ��븴�ã���������߳�

	// ��ʽ2
	void thread_func2(int x) {}
	std::thread mythread2(thread_func2(100));
	mythread2.join();
	//������ʽΪvoid thread_fun(int x)
	//ͬһ���������Դ��븴�ã���������߳�

	// ��ʽ3
	std::thread(thread_func, 1).detach();  // ֱ�Ӵ����̣߳� û�����֡�  ������ʽΪvoid thread_func(int x)

	1.4 join��detach

	���߳�������һ��Ҫ�ں��߳��������thread����ǰ��ȷ���Ժ��ַ�ʽ�ȴ��߳�ִ�н�����
		��detach��ʽ���������߳������ں�̨���У���ǰ�Ĵ����������ִ�У����ȴ����߳̽��ޡ�
		��join��ʽ���ȴ��������߳���ɣ��Ż��������ִ�С�
	����ͨ��joinable�ж���joinģʽ����detachģʽ��

	eg��
		if (myThread.joinable()) 
			foo.join();

*/

#include <thread>
void thread_2(int x);
void thread_1();
int runThread();


// 2.1 lock��unlock
/*
lock()�� ��Դ����
unlock():  ������Դ
trylock():  �鿴�Ƿ������� �����3�֣�1�� δ����������false, ����ס�� 2�������߳�������������true�� 3��ͬһ���߳��Ѿ���������������������
	������ָ���������������ϵĽ��̣����ھ�����Դ���߱˴�ͨ�Ŷ���ɵ�һ���������������������ã����ǽ��޷��ƽ���ȥ������ϵͳ��������״̬����Զ�ڻ���ȴ��Ľ��̳�Ϊ�������̡�

ͬһ��mutex��������֮��һ��ʱ���ڣ�ֻ����һ���̷߳�������

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
	std::thread th1 (print_block,50,'');//�߳�1����ӡ*
	std::thread th2 (print_block,50,'$');//�߳�2����ӡ$

	th1.join();
	th2.join();
	return 0;
}

���Ϊ��
	**************************************************
	$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


	����ǲ�ͬmutex��������Ϊ���漰��ͬһ��Դ�ľ���������һ�´������п��ܻ���ֽ����ӡ�����������һ���߳̿����޸Ĺ�ͬ��ȫ�ֱ�����

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
  ����lock_guard����ʱ���������Ի�ȡ�ṩ�����Ļ�����������Ȩ�����������뿪lock_guard�����������ʱ��lock_guard�������ͷŻ�����.
  
  lock_guard�ص㣺
  ����������������������Զ������������������ֹ�����
  ������;���������������������Ž���
  ���ܸ���

  ����ʾ����
  #include
#include
#include
int g_i = 0;
std::mutex g_i_mutex;  // protects g_i����������g_i


void safe_increment()
{
	const std::lock_guard<std::mutex> lock(g_i_mutex);
	++g_i;
	std::cout << std::this_thread::get_id() << ": " << g_i << '\n';// g_i_mutex�Զ�����}int main(){
	std::cout << "main id: " <<std::this_thread::get_id()<<std::endl;
	std::cout << "main: " << g_i << '\n';


	std::thread t1(safe_increment);
	std::thread t2(safe_increment);


	t1.join();
	t2.join();


	std::cout << "main: " << g_i << '\n';
}

*/
