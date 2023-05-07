#ifndef MESH_RESOURCE_H
#define MESH_RESOURCE_H

#include <vector>

#include "render/vertex.h"

class MeshResource {
public:
    std::vector<Vertex> verticies;
    std::vector<unsigned int> indices;
};

#endif