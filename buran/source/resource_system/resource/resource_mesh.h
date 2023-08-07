#ifndef MESH_RESOURCE_H
#define MESH_RESOURCE_H

#include <vector>
#include <string>

#include "resource_system/resource/resource.h"
#include "render/vertex.h"

struct ResourceSubMesh {
    std::vector<Vertex> verticies;
    std::vector<unsigned int> indices;
    std::string materialName;

    bool IsEmpty() { return verticies.empty() && indices.empty(); }
};

struct ResourceMesh : public Resource {
    INIT_RESOURCE(ResourceMesh)

    std::vector<Vertex> verticies;
    std::vector<unsigned int> indices;
    std::string materialName;

    std::vector<ResourceSubMesh> subMeshes;
};

#endif