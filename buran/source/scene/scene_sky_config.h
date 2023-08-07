#pragma once

#include <string>
#include <glm/vec4.hpp>

struct SceneSkyConfig {
    std::string skyTexture;
    glm::vec4 skyColor = {0, 0, 0, 1};
};