#include "resource_system.h"

static ResourceSystem* instance;

static std::string texturesRoot = "\\assets\\textures\\";
static std::string modelsRoot = "\\assets\\models\\";
static std::string shadersRoot = "\\shaders\\";

ResourceSystem::ResourceSystem(std::string rootResPath) : rootPath(rootResPath) {
    instance = this;
}

ResourceSystem* ResourceSystem::Get() {
    return instance;
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