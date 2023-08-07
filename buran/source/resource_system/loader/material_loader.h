#pragma once

#include "resource_system/loader/resource_loader.h"

class MaterialLoader : public ResourceLoader {
public:
    MaterialLoader(ResourceSystem* sys) : ResourceLoader(sys) {}
    virtual void Load() override;
};