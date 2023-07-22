#include "screen_quad.h"

#include <GLEW/glew.h>

#include "render/primitives/vertex_array_object.h"
#include "render/buffers.h"
#include "render/shader.h"
#include "render/texture.h"

const unsigned int verticiesElementsCount = 20;
const unsigned int indiciesCount = 6;

ScreenQuad::ScreenQuad() {
    float verticies[] = {
        -1, -1, 0, 0, 0,
         1, -1, 0, 1, 0,
         1,  1, 0, 1, 1,
        -1,  1, 0, 0, 1
    };

    unsigned int indicies[] = {
        0, 1, 2,
        0, 2, 3
    };

    vao = new VertexArrayObject();

    vao->Bind();
    
    vertexBuffer = new VertexBuffer((void*)verticies, sizeof(float) * verticiesElementsCount);
    indexBuffer = new IndexBuffer(indicies, sizeof(unsigned int) * indiciesCount);

    vertexBuffer->Bind();
    indexBuffer->Bind();
    
    vao->UnBind();

    vertexBuffer->UnBind();
    indexBuffer->UnBind();
}

void ScreenQuad::Draw(Shader* shader, Texture* texture) {
    vao->Bind();

    vertexBuffer->Bind();
    indexBuffer->Bind();

    texture->Use();

    shader->Use();
    shader->BindVertexAttributes();

    glDrawElements(GL_TRIANGLES, indiciesCount, GL_UNSIGNED_INT, 0);

    texture->Deactivate();

    vertexBuffer->UnBind();
    indexBuffer->UnBind();

    vao->UnBind();
}