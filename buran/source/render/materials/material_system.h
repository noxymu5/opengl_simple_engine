#pragma once

#include <map>
#include <vector>
#include <string>

#include "resource_system/resource_system.h"
#include "render/materials/material.h"
#include "render/materials/material_instance.h"

class MaterialSystem {
public:
    static MaterialSystem* Get();
    MaterialSystem(ResourceSystem* resSys);
    MaterialInstance* GetMaterialInstance(std::string materialName);

private:
    std::vector<Material*> materials;
    std::map<std::string, MaterialInstance*> materialInstances;
};