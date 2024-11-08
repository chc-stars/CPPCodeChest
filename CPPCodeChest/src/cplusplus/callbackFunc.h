#pragma once
/***
* 回调函数允许一个函数作为参数传递给另一个函数，并在适当的时候被调用。这种机制在异步编程、事件处理、库函数调用等场景中非常常见。
* 以下是对回调函数的详细解释。
* 
* 1、基本概念：
*    一个通过函数指针作为参数传递给另一个函数的函数。接收方可以在适当的时候调用这个函数指针所指向的函数。
* 2、应用场景：
*    1）异步编程：在异步操作完成后调用回调函数，通知调用者操作已完成。这在处理网络请求、文件I/O、定时器等异步任务时非常常见。
*    2）事件处理：在特定事件发生时调用回调函数，处理事件。
*    3）库函数调用：库函数通过回调函数与调用者交互，提供更灵活的功能。
*    4）配置和初始化：在配置和初始化过程中，回调函数可以用在完成某些操作后执行特定的逻辑。
*    5）插件和扩展：在插件和扩展中，回调函数用于扩展系统的功能。
* 
* 3、std::promise 和 std::future的作用：
*    std：：promise 用于设置一个未来的值。
     std::future用与获取这个值，并且可以用来等待这个值的设置。

	 阻塞等待：
	 当你在主线程中调用std::future::get 方法时，如果std::promise的值还没有被设置，get方法会阻塞，
	 直到std::promise的值被设置。 一旦std::promise的值被设置，get方法会返回该值，主线程继续执行。
	 例：
	 
	 // 启动异步并获得future
	  std::future<int> future = sender.startOperation(receiver.getCallbacks());
	 
	 // 主线程继续执行
     std::cout << "主线程继续执行..." << std::endl;

	  // 等待异步操作完成
	 int result = future.get();
	 std::cout << "异步操作完成，结果: " << result << std::endl;


* 示例：回调函数可以用于两个类之间实现通信。
        通过将一个类的方法作为回调函数传递给另一个类。
* 
***/


#include <iostream>
#include <functional>
#include <thread>
#include <chrono>

// Receiver 类的onCompletion, 该方法将在Sender 类的操作完成后被调用

class Receiver
{
	
public:
	// 构造函数
	Receiver() {
		std::cout << "Receiver: 构造函数" << std::endl;
	}

	// 析构函数
	~Receiver() {
		std::cout << "Receiver: 析构函数" << std::endl;
	}


	// 定义回调函数类型
	using Callback = std::function<void(int)>;

	// 设置回调函数
	void  setCallback(Callback callback) {
		callback_ = callback;
	}

	Callback getCallback() const {
		return callback_;
	}
	// 回调函数
	void onCompletion(int result) {
		std::cout << "Receiver: 操作完成，结果：" << result << std::endl;
	}


private:

	Callback callback_;
};


// Sender 类


class Sender {
public:
	// 执行异步操作
	void startOperation(Receiver::Callback callback) {
		// 模拟异步操作
		std::thread([this, callback]() {

			std::this_thread::sleep_for(std::chrono::seconds(2));
			int result = 42;
			// 调用回调函数
			callback(result);
			}).detach();
	}
};

//1 异步处理

//int main() {
//
//	Receiver receiver;
//	Sender sender;
//
//	// 设置回调函数
//	receiver.setCallback(std::bind(&Receiver::onCompletion, &receiver, std::placeholders::_1));
//
//	// 启动异步操作
//	sender.startOperation(receiver.getCallback());
//
//	// 主线程继续执行
//	std::cout << "主线程继续执行..." << std::endl;
//
//	// 为了让主线程等待异步操作完成，这里简单地让主线程睡眠一段时间
//	std::this_thread::sleep_for(std::chrono::seconds(3));
//}


//2  事件处理

//3 库函数调用

#include <iostream>
#include <algorithm>
#include <vector>

// 比较函数
//bool compare(int a, int b) {
//	return a < b;
//}
//
//int main() {
//	std::vector<int> numbers = { 5, 2, 8, 1, 9 };
//
//	// 使用自定义的比较函数进行排序
//	std::sort(numbers.begin(), numbers.end(), compare);
//
//	// 输出排序后的结果
//	for (int num : numbers) {
//		std::cout << num << " ";
//	}
//	std::cout << std::endl;
//
//	return 0;
//}

// 4、 配置和初始化
