#pragma once

//详解C++ 编写String 的构造函数、拷贝构造函数、析构函数和赋值函数


#include <iostream>
#include <cstring>

class String {
private:
    char* str;

public:
    // 构造函数
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

    // 拷贝构造函数
    String(const String& s) {
        str = new char[strlen(s.str) + 1];
        strcpy(str, s.str);
    }

    // 移动构造函数
    String(String&& s) noexcept : str(s.str) {
        s.str = nullptr;
    }

    // 析构函数
    ~String() {
        delete[] str;
    }

    // 赋值运算符
    String& operator=(const String& s) {
        if (this != &s) {
            // 先释放旧资源
            delete[] str;
            // 再分配新资源
            str = new char[strlen(s.str) + 1];
            strcpy(str, s.str);
        }
        return *this;
    }

    // 移动赋值运算符
    String& operator=(String&& s) noexcept {
        if (this != &s) {
            // 释放旧资源
            delete[] str;
            // 移动资源
            str = s.str;
            s.str = nullptr;
        }
        return *this;
    }

    // 获取字符串
    const char* c_str() const {
        return str;
    }
};


// ----------  测试用例 ------------
//String s1("Hello");
//String s2 = s1; // 拷贝构造
//String s3("World");
//s3 = s1; // 赋值
//
//std::cout << "s1: " << s1.c_str() << std::endl;
//std::cout << "s2: " << s2.c_str() << std::endl;
//std::cout << "s3: " << s3.c_str() << std::endl;
