#ifndef SCENE_SKY_CONFIG_H
#define SCENE_SKY_CONFIG_H

#include <string>
#include <glm/vec4.hpp>

struct SceneSkyConfig {
    std::string skyTexture;
    glm::vec4 skyColor = {0, 0, 0, 1};
};

#endif