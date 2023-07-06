#include "material_system.h"

#include "resource_system/resource/resource_material.h"
#include "core/asserts.h"

#include "render/materials/material_simple.h"

static std::map<MaterialType, Material*> materialTypeMap = {
    {MaterialType::SIMPLE, new MaterialSimple()}
};

static MaterialSystem* instance;

MaterialSystem* MaterialSystem::Get() {
    return instance;
}

MaterialSystem::MaterialSystem(ResourceSystem* resSys) {
    instance = this;

    std::map<std::string, ResourceMaterial*> materialResources = resSys->GetAllResourcesOfType<ResourceMaterial>();

    for (auto it = materialTypeMap.begin(); it != materialTypeMap.end(); ++it) {
        it->second->LoadShader(resSys);
    }

    for (auto it = materialResources.begin(); it != materialResources.end(); ++it) {
        ResourceMaterial* res = it->second;

        materialInstances[it->first] = new MaterialInstance(res, materialTypeMap[res->type]);
    }
}

MaterialInstance* MaterialSystem::GetMaterialInstance(std::string materialName) {
    auto it = materialInstances.find(materialName);
    ASSERT(it != materialInstances.end(), "Can not find material by name %s", materialName.c_str())

    return it->second;
}