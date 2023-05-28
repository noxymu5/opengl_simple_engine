#ifndef MESH_RESOURCE_H
#define MESH_RESOURCE_H

#include <vector>
#include <string>

#include "resource_system/resource/resource.h"
#include "render/vertex.h"

struct ResourceMesh : public Resource {
    std::vector<Vertex> verticies;
    std::vector<unsigned int> indices;
    std::string materialName;
};

#endif