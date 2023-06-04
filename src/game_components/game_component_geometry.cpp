#include "game_components/game_component_geometry.h"

#include <GLFW/glfw3.h>
#include "game_components/serializers/game_component_serializer.h"

#include "resource_system/resource/resource_mesh.h"
#include "resource_system/resource/resource_material.h"
#include "resource_system/resource/resource_texture.h"
#include "resource_system/resource_system.h"

BEGIN_SERIALIZER(GameComponentGeometry)
EXPOTR_FIELD(modelName, std::string)
END_SERIALIZER(GameComponentGeometry)

void GameComponentGeometry::Init() {
    vao = new VertexArrayObject();

    ResourceSystem* resSys = ResourceSystem::Get();

    mesh = resSys->GetResource<ResourceMesh>(modelName);

    ResourceMaterial* mat = resSys->GetResource<ResourceMaterial>(mesh->materialName);
    if (!mat->textureName.empty()) {
        ResourceTexture* resTexture = resSys->GetResource<ResourceTexture>(mat->textureName);
        texture = new Texture(*resTexture);    
    }

    vao->Bind();
    
    vertexBuffer = new VertexBuffer((void*)&mesh->verticies[0], sizeof(Vertex) * mesh->verticies.size());
    indexBuffer = new IndexBuffer(&mesh->indices[0], mesh->indices.size() * sizeof(unsigned int));
    
    vertexBuffer->Bind();
    indexBuffer->Bind();
    
    vao->UnBind();

    vertexBuffer->UnBind();
    indexBuffer->UnBind();
}

void GameComponentGeometry::StartDraw() {
    vao->Bind();
    
    if (texture != nullptr) {
        texture->Use();
    }

    vertexBuffer->Bind();
    indexBuffer->Bind();
}

void GameComponentGeometry::EndDraw() {
    glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
    vao->UnBind();

    if (texture != nullptr) {
        texture->Deactivate();
    }

    vertexBuffer->UnBind();
    indexBuffer->UnBind();
}