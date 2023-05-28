#ifndef RESOURCE_MATERIAL_H
#define RESOURCE_MATERIAL_H

#include <string>

#include "resource_system/resource/resource.h"

struct ResourceMaterial : public Resource {
    std::string textureName;
};


#endif