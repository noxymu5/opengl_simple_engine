#ifndef MATERIAL_LOADER_H
#define MATERIAL_LOADER_H

#include "resource_system/loader/resource_loader.h"

class MaterialLoader : public ResourceLoader {
public:
    MaterialLoader(ResourceSystem* sys) : ResourceLoader(sys) {}
    virtual void Load() override;
};

#endif