#include "utils.h"
#include "iostream"
#include <fstream>




bool ensureFileExists(const std::string& filePath) {
    if (!std::filesystem::exists(filePath)) {
        std::ofstream newFile(filePath);
        if (newFile.is_open()) {
            newFile.close();
            return true; // 文件创建成功
        }
        else {
            return false; // 无法创建文件
        }
    }
    else {
        return true; // 文件已经存在
    }
}