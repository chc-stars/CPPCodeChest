#pragma once



#include "yaml-cpp/yaml.h"

#include "utils.h"
#include <iostream>

struct configPara
{

    int VERSION;
    std::string PROJECTNAME;
    std::string CPLUSPLUS_VERSION;
};

int parseConfigFile(configPara& configPara_, std::string filePath);  // yaml �ļ�����



// ************************************** ���� ***********************************

//int main() {
    //
    //configPara cPara;
    //parseConfigFile(cPara, "E:/CODE/GitHub/CPPCodeChest/CPPCodeChest/config/config.yaml");
//}