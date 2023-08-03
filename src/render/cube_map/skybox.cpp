#include "skybox.h"

#include <GLEW/glew.h>

#include "resource_system/resource_system.h"
#include "resource_system/resource/resource_shader.h"

#include "render/primitives/vertex_array_object.h"
#include "render/buffers.h"
#include "render/texture/texture_skybox.h"
#include "render/shader.h"
#include "render/render_context.h"

#include "core/logging.h"

Skybox::Skybox(std::string textureName) {
    ResourceSystem* resSys = ResourceSystem::Get();
    shader = new Shader(resSys->GetResource<ResourceShader>("skybox.glsl"));

    texture = new TextureSkybox(textureName);

    float verticies[] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
    };
    
    unsigned int indicies[] = {
        1, 2, 3,
        1, 3, 0,

        4, 7, 6,
        4, 6, 5,
        
        1, 4, 5,
        1, 5, 0,

        7, 2, 3,
        7, 3, 6,

        5, 6, 3,
        5, 3, 0,

        4, 7, 2,
        4, 2, 1
    };

    vao = new VertexArrayObject();

    vao->Bind();
    
    vertexBuffer = new VertexBuffer((void*)verticies, sizeof(verticies));
    indexBuffer = new IndexBuffer(indicies, sizeof(indicies));

    vertexBuffer->Bind();
    indexBuffer->Bind();
    
    vao->UnBind();

    vertexBuffer->UnBind();
    indexBuffer->UnBind();
}

Skybox::~Skybox() {
    delete(vao);
    delete(vertexBuffer);
    delete(indexBuffer);
    delete(texture);
    delete(shader);
}

void Skybox::Draw(RenderContext ctx) {
    vao->Bind();

    vertexBuffer->Bind();
    indexBuffer->Bind();

    texture->Use();

    shader->Use();
    shader->BindVertexAttributes();

    glm::mat4 view = glm::mat4(glm::mat3(ctx.view));
    shader->SetUniform("uViewProj", ctx.proj * view);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    
    texture->Deactivate();

    vertexBuffer->UnBind();
    indexBuffer->UnBind();

    vao->UnBind();
}