#pragma once
/***

问： 什么是面向对象的思想？

面向对象编程（Object0 - Oriented Programming，OOP）是一种编程范式，它通过将数据和操作这些数据的方法组织在一起，形成“对象”，来实现代码的结构化和模块化。OOP的主要目标是提高代码的可重用性、可维护性和灵活性。以下是OOP的四个特性及其在C++中的实现：
1）	封装：指的是将数据（属性）和操作这些数据的方法（行为）绑定在一起，并隐藏对象的内部状态，只暴露必要的接口给外部使用。实现：使用class或struct定义类。使用访问空置房（public，private和protect）控制成员变量的可见性。
2）	继承：继承允许一个类（派生类或子类）继承另一个类（基类或父类）的属性和方法。有助于代码重用和层次化的类结构。实现：使用：符号进行继承，可以选择public、protected或者private继承。
3）	多态：允许不同类的对象对同一消息做出响应。具体来说，多态分为编译时多态（如函数重载）和运行时多态（如虚函数）。实现：使用虚函数（virtual关键字）和纯虚函数（ = 0）。使用指向基类的指针或应用调用派生类的方法。

4）	抽象：抽象是指从具体的实例中提取出共性的特征，忽略非本质的细节。抽象类和接口是实现抽象的主要方式。实现：使用纯虚函数定义抽象类，抽象类不能实例化，智能作为基类被继承。

总结：
	封装： 将数据和方法绑定在一起，并隐藏内部细节。
	继承：允许一个类继承另一个类的属性和方法，促进代码重用。
	多态：不同类的对象对同一个消息做出响应，增强代码的灵活性。
	抽象：从具体的实例中提取共性的特征，忽略非本质细节，提供更高层次的抽象

	通过这些特性的结合使用，面向对象编程能够构建出更加模块化、可扩展和易于维护的软件系统。C++ 作为一种支持 OOP 的语言，提供了丰富的语法和工具来实现这些特性。
***/


// 1、封装
#include <iostream>

class Person {

private:
	std::string name;
	int age;

public:

	// 构造
	Person(const std::string& n, int a) : name(n), age(a){}

	// 获取名字
	std::string getName() const {
		return name;
	}
	// 设置名字
	void setName(const std::string n) {
		name = n;
	}

	// 获取年龄
	int getAge() const {
		return age;
	}

	// 设置年龄
	void setAge(int a) {
		if (a >= 0) {
			age = a;
		}
	}
};

// 2、继承

class Student : Person {
private:
	std::string studentID;

	Student(const std::string& n, int a, const std::string& id)
		: Person(n, a), studentID(id){}

	// 获取学号
	std::string getStudentID() const {
		return studentID;
	}

	// 设置学号
	void setStudentID(const std::string& id) {
		studentID = id;
	}
};


// 3、多态
class Shape {
public:
	virtual ~Shape(){}
	virtual double area() const = 0; // 纯虚函数
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
//	printArea(&circle);  // 输出圆的面积
//	printArea(&rectangle);  // 输出矩形的面积
//
//	return 0;
//}

// 4.抽象
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

