#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
/***
* 在C++中，lambda表达式(也成为lambda函数或匿名函数)是在C++11 标准中引入的一种方便的编写匿名函数的方式。
* 他们通常用于编写简短的函数对象，这些函数对象可以在需要的地方立即定义和使用

  表达式基本语法如下：
	[]mutable->ReturnType{Statement1; Statement2; ...}(arguments)

	[]：捕获子句，定义了 lambda 表达式可以从外部捕获哪些变量。
	mutable：可选关键字，允许在 lambda 表达式内部修改捕获的变量。
	->ReturnType：返回类型，指定 lambda 表达式的返回类型。
	{Statement1; Statement2; ...}：函数体，包含 lambda 表达式的代码块。
	arguments：参数列表，指定 lambda 表达式接受的参数。

	（一）简单的lanbda表达式

	#include <iostream>

	int main() {
		// 一个简单的 lambda 表达式，打印一个整数
		auto print = [](int n) {
			std::cout << n << std::endl;
		};
		print(10); // 输出：10
		return 0;
	}

	（二）捕获外部变量

	#include <iostream>

	int main() {
		int value = 10;
		// 捕获外部变量 value
		auto printValue = [value]() {
			std::cout << value << std::endl;
		};
		printValue(); // 输出：10
		return 0;
	}

	（三）修改捕获的变量
	#include <iostream>

	int main() {
		int value = 10;
		// 通过 mutable 关键字允许修改捕获的变量
		auto increment = [&value]() mutable {
			value += 1;
			std::cout << value << std::endl;
		};
		increment(); // 输出：11
		return 0;
	}

	（四）使用lambda表达式作为算法的参数

	#include <algorithm>
	#include <vector>
	#include <iostream>

	int main() {
		std::vector<int> numbers = {1, 2, 3, 4, 5};
		// 使用 lambda 表达式作为 find_if 的参数
		auto it = std::find_if(numbers.begin(), numbers.end(), [](int n) {
			return n == 3;
		});
		if (it != numbers.end()) {
			std::cout << "Found: " << *it << std::endl;
		} else {
			std::cout << "Not found" << std::endl;
		}
		return 0;
	}
***/




