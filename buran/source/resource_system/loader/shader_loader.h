#pragma once

#include <string>
#include <sstream>

#include "resource_system/loader/resource_loader.h"
#include "resource_system/resource/resource_shader.h"

class ShaderLoader : public ResourceLoader{
public:
    ShaderLoader(ResourceSystem* sys)  : ResourceLoader(sys) {}
    virtual void Load() override;
private:

    std::stringstream ReadFile(std::string path);
    ResourceShader* ParseFile(std::stringstream& shaderSourceStream);
};