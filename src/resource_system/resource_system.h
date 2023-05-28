#ifndef RESOURCE_SYSTEM_H
#define RESOURCE_SYSTEM_H

#include <string>
#include <vector>
#include <map>

#include "resource_system/resource/resource.h"
#include "core/asserts.h"

class ResourceLoader;

class ResourceSystem {
public:
    ResourceSystem(std::string rootResPath);
    static ResourceSystem* Get();

    std::string GetRoot();
    std::string PathToTexture(std::string path);
    std::string PathToShader(std::string path);
    std::string PathToModel(std::string path);

    void RegisterResource(std::string name, Resource* resource);

    template<class ResT>
    ResT* GetResource(std::string resName) {
        auto it = resources.find(resName);
        ASSERT(it != resources.end(), "Can not find resource by name %s", resName.c_str())
        
        return static_cast<ResT*>(it->second);
    }

private:
    std::string rootPath;
    std::vector<ResourceLoader*> loaders;
    std::map<std::string, Resource*> resources;
};

#endif