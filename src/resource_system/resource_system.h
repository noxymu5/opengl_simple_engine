#ifndef RESOURCE_SYSTEM_H
#define RESOURCE_SYSTEM_H

#include <string>
#include <vector>
#include <map>
#include <iterator>

#include "resource_system/resource/resource.h"
#include "core/asserts.h"

class ResourceLoader;

class ResourceSystem {
public:
    ResourceSystem(std::string rootResPath);
    static ResourceSystem* Get();

    std::string GetRoot();

    template<class ResT>
    void RegisterResource(std::string name, ResT* resource) {
        resourcesMap[ResT::Name()][name] = resource;
    }

    template<class ResT>
    ResT* GetResource(std::string resName) {
        auto resourceMapIt = resourcesMap.find(ResT::Name());
        ASSERT(resourceMapIt != resourcesMap.end(), "Unknown resource type %s", ResT::Name().c_str())

        auto it = resourceMapIt->second.find(resName);
        ASSERT(it != resourceMapIt->second.end(), "Can not find resource by name %s", resName.c_str())
        
        return static_cast<ResT*>(it->second);
    }

    template<class ResT>
    std::map<std::string, ResT*> GetAllResourcesOfType() {
        auto resourceMapIt = resourcesMap.find(ResT::Name());
        ASSERT(resourceMapIt != resourcesMap.end(), "Unknown resource type %s", ResT::Name().c_str())

        std::map<std::string, ResT*> result;
        for(auto resIt = resourceMapIt->second.begin(); resIt != resourceMapIt->second.end(); ++resIt) {
            result[resIt->first] = static_cast<ResT*>(resIt->second);
        }

        return result;
    }

private:
    std::string rootPath;
    std::vector<ResourceLoader*> loaders;
    std::map<std::string, std::map<std::string, Resource*>> resourcesMap;
};

#endif