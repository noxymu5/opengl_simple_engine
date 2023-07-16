#ifndef RESOURCE_MATERIAL_H
#define RESOURCE_MATERIAL_H

#include <string>

#include "resource_system/resource/resource.h"
#include "render/materials/material.h"

struct ResourceMaterial : public Resource {
    INIT_RESOURCE(ResourceMaterial)

    MaterialType type {MaterialType::SIMPLE};
    std::string textureName;
    bool isLit = true;
};


#endif