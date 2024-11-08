#pragma once
/***
* �ص���������һ��������Ϊ�������ݸ���һ�������������ʵ���ʱ�򱻵��á����ֻ������첽��̡��¼������⺯�����õȳ����зǳ�������
* �����ǶԻص���������ϸ���͡�
* 
* 1���������
*    һ��ͨ������ָ����Ϊ�������ݸ���һ�������ĺ��������շ��������ʵ���ʱ������������ָ����ָ��ĺ�����
* 2��Ӧ�ó�����
*    1���첽��̣����첽������ɺ���ûص�������֪ͨ�����߲�������ɡ����ڴ������������ļ�I/O����ʱ�����첽����ʱ�ǳ�������
*    2���¼��������ض��¼�����ʱ���ûص������������¼���
*    3���⺯�����ã��⺯��ͨ���ص�����������߽������ṩ�����Ĺ��ܡ�
*    4�����úͳ�ʼ���������úͳ�ʼ�������У��ص����������������ĳЩ������ִ���ض����߼���
*    5���������չ���ڲ������չ�У��ص�����������չϵͳ�Ĺ��ܡ�
* 
* 3��std::promise �� std::future�����ã�
*    std����promise ��������һ��δ����ֵ��
     std::future�����ȡ���ֵ�����ҿ��������ȴ����ֵ�����á�

	 �����ȴ���
	 ���������߳��е���std::future::get ����ʱ�����std::promise��ֵ��û�б����ã�get������������
	 ֱ��std::promise��ֵ�����á� һ��std::promise��ֵ�����ã�get�����᷵�ظ�ֵ�����̼߳���ִ�С�
	 ����
	 
	 // �����첽�����future
	  std::future<int> future = sender.startOperation(receiver.getCallbacks());
	 
	 // ���̼߳���ִ��
     std::cout << "���̼߳���ִ��..." << std::endl;

	  // �ȴ��첽�������
	 int result = future.get();
	 std::cout << "�첽������ɣ����: " << result << std::endl;


* ʾ�����ص�������������������֮��ʵ��ͨ�š�
        ͨ����һ����ķ�����Ϊ�ص��������ݸ���һ���ࡣ
* 
***/


#include <iostream>
#include <functional>
#include <thread>
#include <chrono>

// Receiver ���onCompletion, �÷�������Sender ��Ĳ�����ɺ󱻵���

class Receiver
{
	
public:
	// ���캯��
	Receiver() {
		std::cout << "Receiver: ���캯��" << std::endl;
	}

	// ��������
	~Receiver() {
		std::cout << "Receiver: ��������" << std::endl;
	}


	// ����ص���������
	using Callback = std::function<void(int)>;

	// ���ûص�����
	void  setCallback(Callback callback) {
		callback_ = callback;
	}

	Callback getCallback() const {
		return callback_;
	}
	// �ص�����
	void onCompletion(int result) {
		std::cout << "Receiver: ������ɣ������" << result << std::endl;
	}


private:

	Callback callback_;
};


// Sender ��


class Sender {
public:
	// ִ���첽����
	void startOperation(Receiver::Callback callback) {
		// ģ���첽����
		std::thread([this, callback]() {

			std::this_thread::sleep_for(std::chrono::seconds(2));
			int result = 42;
			// ���ûص�����
			callback(result);
			}).detach();
	}
};

//1 �첽����

//int main() {
//
//	Receiver receiver;
//	Sender sender;
//
//	// ���ûص�����
//	receiver.setCallback(std::bind(&Receiver::onCompletion, &receiver, std::placeholders::_1));
//
//	// �����첽����
//	sender.startOperation(receiver.getCallback());
//
//	// ���̼߳���ִ��
//	std::cout << "���̼߳���ִ��..." << std::endl;
//
//	// Ϊ�������̵߳ȴ��첽������ɣ�����򵥵������߳�˯��һ��ʱ��
//	std::this_thread::sleep_for(std::chrono::seconds(3));
//}


//2  �¼�����

//3 �⺯������

#include <iostream>
#include <algorithm>
#include <vector>

// �ȽϺ���
//bool compare(int a, int b) {
//	return a < b;
//}
//
//int main() {
//	std::vector<int> numbers = { 5, 2, 8, 1, 9 };
//
//	// ʹ���Զ���ıȽϺ�����������
//	std::sort(numbers.begin(), numbers.end(), compare);
//
//	// ��������Ľ��
//	for (int num : numbers) {
//		std::cout << num << " ";
//	}
//	std::cout << std::endl;
//
//	return 0;
//}

// 4�� ���úͳ�ʼ��
