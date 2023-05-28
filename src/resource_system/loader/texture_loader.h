#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <string>
#include <vector>

#include "resource_system/loader/resource_loader.h"

class TextureLoader : public ResourceLoader {
public:
    TextureLoader(ResourceSystem* sys) : ResourceLoader(sys) {}
    virtual void Load() override;
};

#endif