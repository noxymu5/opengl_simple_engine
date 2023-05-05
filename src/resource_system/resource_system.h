#ifndef RESOURCE_SYSTEM_H
#define RESOURCE_SYSTEM_H

#include <string>

class ResourceSystem {
public:
    ResourceSystem(std::string rootResPath);
    static ResourceSystem* Get();

    std::string PathToTexture(std::string path);
    std::string PathToShader(std::string path);
private:
    std::string rootPath;
};

#endif