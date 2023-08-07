#pragma once

#include <vector>
#include <string>

#include "resource.h"

enum class ShaderType {
    Udefined = -1,
    Vertex,
    Fragment,

    Count
};

struct ResourceShader : Resource {
    INIT_RESOURCE(ResourceShader)

    std::string* shaderSources;
    std::vector<std::string> attributeTypes;
};