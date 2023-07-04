#ifndef LIGHT_H
#define LIGHT_H

#include <glm/vec3.hpp>

#include "scene/game_object.h"

enum class LIGHT_TYPE {
    DIRECTIONAL,
    POINT
};

class Light : public GameObject {
public:
    LIGHT_TYPE type { LIGHT_TYPE::POINT };
    glm::vec3 color {1.0f};
    float distance = 3;
};

#endif