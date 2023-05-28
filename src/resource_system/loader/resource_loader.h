#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <filesystem>

#include "resource_system/resource_system.h"

class ResourceLoader {
public:
    ResourceLoader(ResourceSystem* resourceSystem);
    virtual void Load() = 0;
protected:
    ResourceSystem* resSys;

    void CollectItemsPath(std::vector<std::filesystem::path>& itemsPath, std::string directory);
};

#endif