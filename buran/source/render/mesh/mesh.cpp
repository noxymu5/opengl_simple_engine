#include "mesh.h"

#include <glbinding/gl/gl.h>

#include "resource_system/resource/resource_material.h"
#include "resource_system/resource/resource_texture.h"
#include "resource_system/resource_system.h"
#include "render/materials/material_instance.h"
#include "render/materials/material_system.h"

Mesh::Mesh(std::string modelName, MaterialOverride& materialOverride) {
    ResourceSystem* resSys = ResourceSystem::Get();

    ResourceMesh* mesh = resSys->GetResource<ResourceMesh>(modelName);

    for (int subMeshIdx = 0; subMeshIdx < mesh->subMeshes.size(); ++subMeshIdx) {
        SubMesh* subMesh = new SubMesh(&mesh->subMeshes[subMeshIdx], materialOverride.mainMaterialName);
        subMeshes.push_back(subMesh);
    }
}

void Mesh::Draw( RenderContext ctx) {
    for (int idx = 0; idx < subMeshes.size(); ++idx) {
        subMeshes[idx]->Draw(ctx);
    }
}

SubMesh::SubMesh(ResourceSubMesh* resource, std::string& overridenMaterialName) {
    vao = new VertexArrayObject();
    ResourceSystem* resSys = ResourceSystem::Get();

    if (overridenMaterialName.empty()) {
        material = MaterialSystem::Get()->GetMaterialInstance(resource->materialName);
    } else {
        material = MaterialSystem::Get()->GetMaterialInstance(overridenMaterialName);
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

void SubMesh::Draw(RenderContext ctx) {
    vao->Bind();

    vertexBuffer->Bind();
    indexBuffer->Bind();

    material->Activate(ctx);

    gl::glDrawElements(gl::GL_TRIANGLES, indexCount, gl::GL_UNSIGNED_INT, 0);

    material->Deactivate();

    vertexBuffer->UnBind();
    indexBuffer->UnBind();

    vao->UnBind();
}
