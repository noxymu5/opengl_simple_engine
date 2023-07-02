#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

#include "render/shader.h"
#include "resource_system/resource/resource_mesh.h"

#include "render/buffers.h"
#include "render/vertex_array_object.h"
#include "render/texture.h"

#include "render/render_context.h"

class SubMesh {
public:
    SubMesh(ResourceSubMesh* resourceMesh);
    void Draw(Shader* shader, RenderContext ctx);

private:
    Texture* texture = nullptr;
    VertexArrayObject* vao;
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;
    int indexCount;
};

class Mesh {
public:
    Mesh(std::string modelName);
    void Draw(Shader* shader, RenderContext ctx);

private:
    std::vector<SubMesh*> subMeshes;
};

#endif