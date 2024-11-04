#pragma once

#include <iostream>
#include <memory>
/***
  (一)，unique_ptr
  注： 该指针无法进行拷贝构造和赋值构造操作
  1） 初始化
     std::unique_ptr<AA>p1(new AA('dd')); 
	 std::unique_ptr<AA>p1 = std::make_unique<AA>('dd');

  .get() 方法返回裸指针
  传引用，（不能传值，因为unique_ptr没有拷贝构造函数），见func，func1，func2

  (二) shared_ptr
  shared_ptr:当一个资源需要再多个对象之间共享时，就无法使用unique_ptr.这是需要使用到shared_ptr，
  它通过引用计数的方式来对资源进行控制，但它存在循环引用的问题，需要结合weak_ptr来避免

  (三) weak_ptr
  weak_ptr是配合share_ptr的，防止循环引用
  1) 不控制对象生命周期，但是，它知道对象是否还活着
  2) lock()函数它他们提升为shared_ptr,如果对象还活着，返回有效的shared_ptr,如果对象死了，提升失败，返回空的shared_ptr.
  3) 提升的行为（lock()）是线程安全的。



***/


// 例

class AA {

public:
	std::string m_name;
	AA() { std::cout << m_name << "调用了构造函数AA() \n"; }
	AA(const std::string& name) :m_name(name) { std::cout << m_name << "调用了构造函数AA()" <<m_name; }
	~AA() { std::cout << m_name << "调用了构造函数AA() << " << m_name; }

	std::weak_ptr<AA> m_P;
};

void func(std::unique_ptr<AA> pp) {  // 传值 （报错）
	std::cout << pp->m_name;
}
void func1(std::unique_ptr<AA> &pp) {  // 传地址（可以）
	std::cout << pp->m_name;
}

void func2(std::unique_ptr<AA> *pp) {  //传指针(推荐)
	std::cout << (*pp)->m_name;
}

//
//int main() {
//	AA* p = new AA("dd");   // 不会调用析构函数
//	std::unique_ptr<AA>p1(p);  
//	std::unique_ptr<AA>p2 = std::make_unique<AA>("xx");
//
//	// 
//	std::shared_ptr<AA> pS = std::make_shared <AA>("cd");
//	std::cout << pS.use_count();  //
//
//	// 循环引用
//	std::shared_ptr<AA> pA = std::make_shared <AA>("cdA");
//	std::shared_ptr<AA> pB = std::make_shared <AA>("cdB");
//
//	pA->m_P = pB;
//	pB->m_P = pA;
//
//	shared_ptr<AA> pp = pA->m_P.lock();  // 把weak提升为shared
//	if (pp == nullptr) {
//		cout << "语句块内部：PA-》m_p已过期. \n";
//	}
//	else {
//		cout << "语句块内部：pp->m_name=" << pp->m_name << endl;
//	}
//
//}

