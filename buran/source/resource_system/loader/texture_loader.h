#pragma once

#include <string>
#include <vector>

#include "resource_system/loader/resource_loader.h"

class TextureLoader : public ResourceLoader {
public:
    TextureLoader(ResourceSystem* sys) : ResourceLoader(sys) {}
    virtual void Load() override;
};