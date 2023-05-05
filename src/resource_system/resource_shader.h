#ifndef RESOURCE_SHADER_H
#define RESOURCE_SHADER_H

#include <vector>
#include <string>

enum class ShaderType {
    Udefined = -1,
    Vertex,
    Fragment,

    Count
};

struct ResourceShader {
    std::string* shaderSources;
    std::vector<std::string> attributeTypes;
};

#endif