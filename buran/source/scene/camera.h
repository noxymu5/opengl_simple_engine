#pragma once

#include <glm/mat4x4.hpp>

#include "scene/game_object.h"

class Camera : public GameObject {
public:
    glm::mat4 GetViewMatrix();
};