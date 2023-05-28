#include "resource_system/loader/resource_loader.h"

ResourceLoader::ResourceLoader(ResourceSystem* resourceSystem) {
    resSys = resourceSystem;
}

void ResourceLoader::CollectItemsPath(std::vector<std::filesystem::path>& itemsPath, std::string directory) {
    for (auto const& dirEntry : std::filesystem::directory_iterator{directory}) {
        std::string pathToEntry = dirEntry.path().string();

        if (dirEntry.is_directory()) {
            CollectItemsPath(itemsPath, pathToEntry);
        } else {
            itemsPath.push_back(dirEntry.path());
        }
    }
}