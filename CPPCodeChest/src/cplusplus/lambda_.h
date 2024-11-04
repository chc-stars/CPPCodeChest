#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
/***
* ��C++�У�lambda���ʽ(Ҳ��Ϊlambda��������������)����C++11 ��׼�������һ�ַ���ı�д���������ķ�ʽ��
* ����ͨ�����ڱ�д��̵ĺ���������Щ���������������Ҫ�ĵط����������ʹ��

  ���ʽ�����﷨���£�
	[]mutable->ReturnType{Statement1; Statement2; ...}(arguments)

	[]�������Ӿ䣬������ lambda ���ʽ���Դ��ⲿ������Щ������
	mutable����ѡ�ؼ��֣������� lambda ���ʽ�ڲ��޸Ĳ���ı�����
	->ReturnType���������ͣ�ָ�� lambda ���ʽ�ķ������͡�
	{Statement1; Statement2; ...}�������壬���� lambda ���ʽ�Ĵ���顣
	arguments�������б�ָ�� lambda ���ʽ���ܵĲ�����

	��һ���򵥵�lanbda���ʽ

	#include <iostream>

	int main() {
		// һ���򵥵� lambda ���ʽ����ӡһ������
		auto print = [](int n) {
			std::cout << n << std::endl;
		};
		print(10); // �����10
		return 0;
	}

	�����������ⲿ����

	#include <iostream>

	int main() {
		int value = 10;
		// �����ⲿ���� value
		auto printValue = [value]() {
			std::cout << value << std::endl;
		};
		printValue(); // �����10
		return 0;
	}

	�������޸Ĳ���ı���
	#include <iostream>

	int main() {
		int value = 10;
		// ͨ�� mutable �ؼ��������޸Ĳ���ı���
		auto increment = [&value]() mutable {
			value += 1;
			std::cout << value << std::endl;
		};
		increment(); // �����11
		return 0;
	}

	���ģ�ʹ��lambda���ʽ��Ϊ�㷨�Ĳ���

	#include <algorithm>
	#include <vector>
	#include <iostream>

	int main() {
		std::vector<int> numbers = {1, 2, 3, 4, 5};
		// ʹ�� lambda ���ʽ��Ϊ find_if �Ĳ���
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




