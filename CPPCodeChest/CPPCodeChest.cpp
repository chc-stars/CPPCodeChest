// CPPCodeChest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _SILENCE_CXX17_RESULT_OF_DEPRECATION_WARNING


#include <iostream>
#include <chrono>

#include "src/common/utils.h"
#include "src/common/logger.h"
#include "src/common/mysqlDB.h"
#include "src/common/parseYamlFile.h"
#include "src/thread/threadPool.h"
#include "src/thread/threadPool.hpp"


#include "src/cplusplus/CPP_FUNC_API.h"


int main()
{

    // 获取当前时间点
    auto start = std::chrono::high_resolution_clock::now();

  

    // 获取当前时间点
    auto end = std::chrono::high_resolution_clock::now();

    // 计算时间差
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;

}


