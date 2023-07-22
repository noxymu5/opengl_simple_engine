#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <map>

#include "render/shader.h"
#include "resource_system/resource/resource_mesh.h"

#include "render/buffers.h"
#include "render/primitives/vertex_array_object.h"
#include "render/materials/material_instance.h"

#include "render/render_context.h"

struct MaterialOverride {
    std::string mainMaterialName;
    std::map<std::string, std::string> submeshToMaterial;
};

class SubMesh {
public:
    SubMesh(ResourceSubMesh* resourceMesh, std::string& overridenMaterialName);
    void Draw(RenderContext ctx);

private:
    MaterialInstance* material;
    VertexArrayObject* vao;
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;
    int indexCount;
};

class Mesh {
public:
    Mesh(std::string modelName, MaterialOverride& materialOverride);
    void Draw(RenderContext ctx);

private:
    std::vector<SubMesh*> subMeshes;
};

#endif