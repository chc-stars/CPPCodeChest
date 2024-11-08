#pragma once
/***
* 
* 
* �������Ƕ��̱߳���е�һ����Ҫͬ�����ƣ����ڱ���������Դ����ֹ���ݾ����;�̬������ͨ��ʹ��std::mutex��std::lock_guard,������Ч�Ĺ���ͱ���������Դ��ȷ�����̳߳������ȷ�ԺͰ�ȫ�ԡ�
* 
* ���ã�����������Դ����ֹ���ݾ�����ȷ���̰߳�ȫ
* 
* �����÷���
* 
*  std::metux mtx��
*   
*   1���Զ������ڴ�
*  	std::lock_guard<std::mutex> lock(mtx);    // 1���Զ������ڴ�
*   
*   2��ʹ��lock() �� unlock(),�м������Ҫ�����ı���
* 	    //mtx.lock();
		++sharedCounter;
		//mtx.unlock();
* 
***/

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>



// ������Դ
int sharedCounter = 0;

// ������
std::mutex mtx;

// �̺߳���
void incrementCounter(int id) {
	for (int i = 0; i < 1000000; ++i) {
		// ����������
		mtx.lock();
		// std::lock_guard<std::mutex> lock(mtx);
		++sharedCounter;
		mtx.unlock();
	}

	std::cout << "Thread " << id << " finished." << std::endl;
}

//int main() {
//    // ��������߳�
//    std::vector<std::thread> threads;
//    for (int i = 0; i < 10; ++i) {
//        threads.emplace_back(incrementCounter, i);
//    }
//
//    // �ȴ������߳����
//    for (auto& t : threads) {
//        t.join();
//    }
//
//    // ������յĹ��������ֵ
//    std::cout << "Final value of sharedCounter: " << sharedCounter << std::endl;
//
//    return 0;
//}