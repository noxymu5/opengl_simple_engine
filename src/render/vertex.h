#ifndef VERTEX_H
#define VERTEX_H

#include "core/glm_declarations.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

#endif