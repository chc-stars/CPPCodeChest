#pragma once

#include <iostream>
#include <memory>
/***
  (һ)��unique_ptr
  ע�� ��ָ���޷����п�������͸�ֵ�������
  1�� ��ʼ��
     std::unique_ptr<AA>p1(new AA('dd')); 
	 std::unique_ptr<AA>p1 = std::make_unique<AA>('dd');

  .get() ����������ָ��
  �����ã������ܴ�ֵ����Ϊunique_ptrû�п������캯��������func��func1��func2

  (��) shared_ptr
  shared_ptr:��һ����Դ��Ҫ�ٶ������֮�乲��ʱ�����޷�ʹ��unique_ptr.������Ҫʹ�õ�shared_ptr��
  ��ͨ�����ü����ķ�ʽ������Դ���п��ƣ���������ѭ�����õ����⣬��Ҫ���weak_ptr������

  (��) weak_ptr
  weak_ptr�����share_ptr�ģ���ֹѭ������
  1) �����ƶ����������ڣ����ǣ���֪�������Ƿ񻹻���
  2) lock()��������������Ϊshared_ptr,������󻹻��ţ�������Ч��shared_ptr,����������ˣ�����ʧ�ܣ����ؿյ�shared_ptr.
  3) ��������Ϊ��lock()�����̰߳�ȫ�ġ�



***/


// ��

class AA {

public:
	std::string m_name;
	AA() { std::cout << m_name << "�����˹��캯��AA() \n"; }
	AA(const std::string& name) :m_name(name) { std::cout << m_name << "�����˹��캯��AA()" <<m_name; }
	~AA() { std::cout << m_name << "�����˹��캯��AA() << " << m_name; }

	std::weak_ptr<AA> m_P;
};

void func(std::unique_ptr<AA> pp) {  // ��ֵ ������
	std::cout << pp->m_name;
}
void func1(std::unique_ptr<AA> &pp) {  // ����ַ�����ԣ�
	std::cout << pp->m_name;
}

void func2(std::unique_ptr<AA> *pp) {  //��ָ��(�Ƽ�)
	std::cout << (*pp)->m_name;
}

//
//int main() {
//	AA* p = new AA("dd");   // ���������������
//	std::unique_ptr<AA>p1(p);  
//	std::unique_ptr<AA>p2 = std::make_unique<AA>("xx");
//
//	// 
//	std::shared_ptr<AA> pS = std::make_shared <AA>("cd");
//	std::cout << pS.use_count();  //
//
//	// ѭ������
//	std::shared_ptr<AA> pA = std::make_shared <AA>("cdA");
//	std::shared_ptr<AA> pB = std::make_shared <AA>("cdB");
//
//	pA->m_P = pB;
//	pB->m_P = pA;
//
//	shared_ptr<AA> pp = pA->m_P.lock();  // ��weak����Ϊshared
//	if (pp == nullptr) {
//		cout << "�����ڲ���PA-��m_p�ѹ���. \n";
//	}
//	else {
//		cout << "�����ڲ���pp->m_name=" << pp->m_name << endl;
//	}
//
//}

