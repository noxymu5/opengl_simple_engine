#include "mesh.h"

#include <GLFW/glfw3.h>

#include "resource_system/resource/resource_material.h"
#include "resource_system/resource/resource_texture.h"
#include "resource_system/resource_system.h"

Mesh::Mesh(std::string modelName) {
    ResourceSystem* resSys = ResourceSystem::Get();

    ResourceMesh* mesh = resSys->GetResource<ResourceMesh>(modelName);

    for (int subMeshIdx = 0; subMeshIdx < mesh->subMeshes.size(); ++subMeshIdx) {
        SubMesh* subMesh = new SubMesh(&mesh->subMeshes[subMeshIdx]);
        subMeshes.push_back(subMesh);
    }
}

void Mesh::Draw(Shader* shader, RenderContext ctx) {
    for (int idx = 0; idx < subMeshes.size(); ++idx) {
        subMeshes[idx]->Draw(shader, ctx);
    }
}

SubMesh::SubMesh(ResourceSubMesh* resource) {
    vao = new VertexArrayObject();
    ResourceSystem* resSys = ResourceSystem::Get();

    ResourceMaterial* mat = resSys->GetResource<ResourceMaterial>(resource->materialName);
    if (!mat->textureName.empty()) {
        ResourceTexture* resTexture = resSys->GetResource<ResourceTexture>(mat->textureName);
        texture = new Texture(*resTexture);    
    }

    vao->Bind();
    
    vertexBuffer = new VertexBuffer((void*)&resource->verticies[0], sizeof(Vertex) * resource->verticies.size());
    indexBuffer = new IndexBuffer(&resource->indices[0], resource->indices.size() * sizeof(unsigned int));
    
    indexCount = resource->indices.size();

    vertexBuffer->Bind();
    indexBuffer->Bind();
    
    vao->UnBind();

    vertexBuffer->UnBind();
    indexBuffer->UnBind();
}

void SubMesh::Draw(Shader* shader, RenderContext ctx) {
    vao->Bind();
    
    if (texture != nullptr) {
        texture->Use();
    }

    vertexBuffer->Bind();
    indexBuffer->Bind();

    shader->Use();
    shader->BindVertexAttributes();
    shader->SetUniform("trf", ctx.viewProj * ctx.model);

    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

    if (texture != nullptr) {
        texture->Deactivate();
    }

    vertexBuffer->UnBind();
    indexBuffer->UnBind();

    vao->UnBind();
}
