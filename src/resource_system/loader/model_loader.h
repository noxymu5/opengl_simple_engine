#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <string>

#include "resource_system/loader/resource_loader.h"

class ModelLoader : public ResourceLoader {
public:
    ModelLoader(ResourceSystem* sys) : ResourceLoader(sys) {}
    virtual void Load() override;
};

#endif