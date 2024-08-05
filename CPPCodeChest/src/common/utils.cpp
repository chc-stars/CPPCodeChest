#include "utils.h"
#include "iostream"
#include <fstream>




bool ensureFileExists(const std::string& filePath) {
    if (!std::filesystem::exists(filePath)) {
        std::ofstream newFile(filePath);
        if (newFile.is_open()) {
            newFile.close();
            return true; // �ļ������ɹ�
        }
        else {
            return false; // �޷������ļ�
        }
    }
    else {
        return true; // �ļ��Ѿ�����
    }
}