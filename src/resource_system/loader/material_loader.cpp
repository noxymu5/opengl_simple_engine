#include "material_loader.h"

#include <yaml-cpp/yaml.h>

#include "core/logging.h"
#include "resource_system/resource/resource_material.h"

static std::string materialsRoot = "\\assets\\materials\\";

void MaterialLoader::Load() {
    std::string materialsFolderPath = resSys->GetRoot() + materialsRoot;

    LOG("Load materials from folder %s", materialsFolderPath.c_str())

    std::filesystem::directory_entry entry{materialsFolderPath};
    ASSERT(entry.exists(), "Directory %s does not exist", materialsFolderPath.c_str())
    ASSERT(entry.is_directory(), "Path %s does not lead to directory", materialsFolderPath.c_str())

    std::vector<std::filesystem::path> materialsPath;
    CollectItemsPath(materialsPath, materialsFolderPath);
    
    for(std::filesystem::path path : materialsPath) {
        std::string pathAsString = path.string();
        std::string fileName = path.filename().string();

        YAML::Node yamlMaterial = YAML::LoadFile(pathAsString.c_str());
        if (!yamlMaterial["properties"]) {
            LOG("Invalid file contents for %s. Skip loading", pathAsString.c_str())
            continue;
        }

        YAML::Node materialProperties = yamlMaterial["properties"];
        ResourceMaterial* resource = new ResourceMaterial();

        if (materialProperties["textureName"]) {
            resource->textureName = materialProperties["textureName"].as<std::string>();
        }

        resSys->RegisterResource<ResourceMaterial>(fileName, resource);
        LOG("Finished loading %s", fileName.c_str())
    }
}