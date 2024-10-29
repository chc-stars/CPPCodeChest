#pragma once

//���C++ ��дString �Ĺ��캯�����������캯�������������͸�ֵ����


#include <iostream>
#include <cstring>

class String {
private:
    char* str;

public:
    // ���캯��
    String(const char* s = "") {
        if (s == nullptr) {
            str = new char[1];
            *str = '\0';
        }
        else {
            str = new char[strlen(s) + 1];
            strcpy(str, s);
        }
    }

    // �������캯��
    String(const String& s) {
        str = new char[strlen(s.str) + 1];
        strcpy(str, s.str);
    }

    // �ƶ����캯��
    String(String&& s) noexcept : str(s.str) {
        s.str = nullptr;
    }

    // ��������
    ~String() {
        delete[] str;
    }

    // ��ֵ�����
    String& operator=(const String& s) {
        if (this != &s) {
            // ���ͷž���Դ
            delete[] str;
            // �ٷ�������Դ
            str = new char[strlen(s.str) + 1];
            strcpy(str, s.str);
        }
        return *this;
    }

    // �ƶ���ֵ�����
    String& operator=(String&& s) noexcept {
        if (this != &s) {
            // �ͷž���Դ
            delete[] str;
            // �ƶ���Դ
            str = s.str;
            s.str = nullptr;
        }
        return *this;
    }

    // ��ȡ�ַ���
    const char* c_str() const {
        return str;
    }
};


// ----------  �������� ------------
//String s1("Hello");
//String s2 = s1; // ��������
//String s3("World");
//s3 = s1; // ��ֵ
//
//std::cout << "s1: " << s1.c_str() << std::endl;
//std::cout << "s2: " << s2.c_str() << std::endl;
//std::cout << "s3: " << s3.c_str() << std::endl;
