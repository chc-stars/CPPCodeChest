#include "parseYamlFile.h"


int parseConfigFile(configPara& configPara_, std::string filePath) {

    if (std::filesystem::exists(filePath)) {
        std::cout << "Path exists: " << filePath << std::endl;
    }
    else {
        std::cout << "Path does not exist: " << filePath << std::endl;
        return -1;
    }
   
    try {
        YAML::Node config = YAML::LoadFile(filePath);

        // 读取 BASE INFO 下的子节点
        YAML::Node baseInfo = config["BASE INFO"];
        if (!baseInfo) {
            throw std::runtime_error("Base Info section not found.");
        }

        std::string version = baseInfo["VERSION"].as<std::string>();
        std::string projectName = baseInfo["PROJECTNAME"].as<std::string>();
        std::string cplusplusVersion = baseInfo["CPLUSPLUS VERSION"].as<std::string>();

        std::cout << "Version: " << version << std::endl;
        std::cout << "Project Name: " << projectName << std::endl;
        std::cout << "C++ Version: " << cplusplusVersion << std::endl;
        
        return 0;
    }
    catch (const YAML::Exception& e) {
        std::cerr << "Error loading YAML file: " << e.what() << std::endl;
        return -1;
    }
    
}

