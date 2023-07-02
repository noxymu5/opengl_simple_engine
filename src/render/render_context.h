#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

#include <glm/mat4x4.hpp>

struct RenderContext {
    glm::mat4 viewProj;
    glm::mat4 model;
};

#endif