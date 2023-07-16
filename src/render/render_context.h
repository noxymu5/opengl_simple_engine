#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include <vector>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "render/light_data.h"

struct RenderContext {
    glm::vec3 viewPos;
    glm::mat4 viewProj;
    glm::mat4 model;

    SceneLightsData* lightData;
};

#endif