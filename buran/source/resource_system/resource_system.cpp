#include "resource_system.h"

#include "resource_system/loader/texture_loader.h"
#include "resource_system/loader/model_loader.h"
#include "resource_system/loader/shader_loader.h"
#include "resource_system/loader/material_loader.h"
#include "core/logging.h"

static ResourceSystem* instance;

ResourceSystem::ResourceSystem(std::string rootResPath) : rootPath(rootResPath) {
    instance = this;

    loaders.push_back(new MaterialLoader(this));
    loaders.push_back(new ShaderLoader(this));
    loaders.push_back(new TextureLoader(this));
    loaders.push_back(new ModelLoader(this));

    LOG("Start Loading resources")

    for(ResourceLoader* loader : loaders) {
        loader->Load();
    }
}

ResourceSystem* ResourceSystem::Get() {
    return instance;
}

std::string ResourceSystem::GetRoot() {
    return rootPath;
}