#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <string>
#include <sstream>

#include "resource_system/resource/resource_shader.h"

class ShaderLoader {
public:
    ShaderLoader(std::string path);
    ResourceShader Get() { return resource; }
private:
    std::stringstream shaderSourceStream;

    ResourceShader resource;

    void ReadFile(std::string path);
    void ParseFile();
};

#endif