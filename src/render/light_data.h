#ifndef LIGHT_DATA_H
#define LIGHT_DATA_H

#include <glm/vec3.hpp>

#include "scene/light.h"

struct LightData {
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;
    float distance;

    LIGHT_TYPE type;
};

#endif