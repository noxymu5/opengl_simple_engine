#include "resource_system.h"

#include "resource_system/loader/texture_loader.h"
#include "resource_system/loader/model_loader.h"
#include "core/logging.h"

static ResourceSystem* instance;

static std::string texturesRoot = "\\assets\\textures\\";
static std::string modelsRoot = "\\assets\\models\\";
static std::string shadersRoot = "\\shaders\\";

ResourceSystem::ResourceSystem(std::string rootResPath) : rootPath(rootResPath) {
    instance = this;

    loaders.push_back(new TextureLoader(this));
    loaders.push_back(new ModelLoader(this));

    LOG("Start Loading resources")

    for(ResourceLoader* loader : loaders) {
        loader->Load();
    }
}

void ResourceSystem::RegisterResource(std::string name, Resource* resource) {
    resources[name] = resource;
}

ResourceSystem* ResourceSystem::Get() {
    return instance;
}

std::string ResourceSystem::GetRoot() {
    return rootPath;
}

std::string ResourceSystem::PathToTexture(std::string path) {
    return rootPath + texturesRoot + path;
}

std::string ResourceSystem::PathToShader(std::string path) {
    return rootPath + shadersRoot + path;
}

std::string ResourceSystem::PathToModel(std::string path) {
    return rootPath + modelsRoot + path;
};