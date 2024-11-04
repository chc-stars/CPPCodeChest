#pragma once
/***

�ʣ� ʲô����������˼�룿

��������̣�Object0 - Oriented Programming��OOP����һ�ֱ�̷�ʽ����ͨ�������ݺͲ�����Щ���ݵķ�����֯��һ���γɡ����󡱣���ʵ�ִ���Ľṹ����ģ�黯��OOP����ҪĿ������ߴ���Ŀ������ԡ���ά���Ժ�����ԡ�������OOP���ĸ����Լ�����C++�е�ʵ�֣�
1��	��װ��ָ���ǽ����ݣ����ԣ��Ͳ�����Щ���ݵķ�������Ϊ������һ�𣬲����ض�����ڲ�״̬��ֻ��¶��Ҫ�Ľӿڸ��ⲿʹ�á�ʵ�֣�ʹ��class��struct�����ࡣʹ�÷��ʿ��÷���public��private��protect�����Ƴ�Ա�����Ŀɼ��ԡ�
2��	�̳У��̳�����һ���ࣨ����������ࣩ�̳���һ���ࣨ������ࣩ�����Ժͷ����������ڴ������úͲ�λ�����ṹ��ʵ�֣�ʹ�ã����Ž��м̳У�����ѡ��public��protected����private�̳С�
3��	��̬������ͬ��Ķ����ͬһ��Ϣ������Ӧ��������˵����̬��Ϊ����ʱ��̬���纯�����أ�������ʱ��̬�����麯������ʵ�֣�ʹ���麯����virtual�ؼ��֣��ʹ��麯���� = 0����ʹ��ָ������ָ���Ӧ�õ���������ķ�����

4��	���󣺳�����ָ�Ӿ����ʵ������ȡ�����Ե����������ԷǱ��ʵ�ϸ�ڡ�������ͽӿ���ʵ�ֳ������Ҫ��ʽ��ʵ�֣�ʹ�ô��麯����������࣬�����಻��ʵ������������Ϊ���౻�̳С�

�ܽ᣺
	��װ�� �����ݺͷ�������һ�𣬲������ڲ�ϸ�ڡ�
	�̳У�����һ����̳���һ��������Ժͷ������ٽ��������á�
	��̬����ͬ��Ķ����ͬһ����Ϣ������Ӧ����ǿ���������ԡ�
	���󣺴Ӿ����ʵ������ȡ���Ե����������ԷǱ���ϸ�ڣ��ṩ���߲�εĳ���

	ͨ����Щ���ԵĽ��ʹ�ã�����������ܹ�����������ģ�黯������չ������ά�������ϵͳ��C++ ��Ϊһ��֧�� OOP �����ԣ��ṩ�˷ḻ���﷨�͹�����ʵ����Щ���ԡ�
***/


// 1����װ
#include <iostream>

class Person {

private:
	std::string name;
	int age;

public:

	// ����
	Person(const std::string& n, int a) : name(n), age(a){}

	// ��ȡ����
	std::string getName() const {
		return name;
	}
	// ��������
	void setName(const std::string n) {
		name = n;
	}

	// ��ȡ����
	int getAge() const {
		return age;
	}

	// ��������
	void setAge(int a) {
		if (a >= 0) {
			age = a;
		}
	}
};

// 2���̳�

class Student : Person {
private:
	std::string studentID;

	Student(const std::string& n, int a, const std::string& id)
		: Person(n, a), studentID(id){}

	// ��ȡѧ��
	std::string getStudentID() const {
		return studentID;
	}

	// ����ѧ��
	void setStudentID(const std::string& id) {
		studentID = id;
	}
};


// 3����̬
class Shape {
public:
	virtual ~Shape(){}
	virtual double area() const = 0; // ���麯��
};

class  Circle : Shape
{
public:
	
	Circle(double r) : radius(r) {}
	double area() const override {
		return 3.14159 * radius * radius;

	}
private:
	double radius;
};

class Rectangle : public Shape {
private:
	double width;
	double height;

public:
	Rectangle(double w, double h) : width(w), height(h) {}

	double area() const override {
		return width * height;
	}
};

void printArea(const Shape* shape) {
	std::cout << "Area: " << shape->area() << std::endl;
}

//int main() {
//	Circle circle(5.0);
//	Rectangle rectangle(4.0, 6.0);
//
//	printArea(&circle);  // ���Բ�����
//	printArea(&rectangle);  // ������ε����
//
//	return 0;
//}

// 4.����
class Animal {
public:
	virtual ~Animal() {}
	virtual void makeSound() const = 0;
};

class Dog : Animal
{
public:
	void makeSound() const override{
		std::cout << "woof" << std::endl;
	}

};

class Cat : public Animal {
public:
	void makeSound() const override {
		std::cout << "Meow meow!" << std::endl;
	}
};

