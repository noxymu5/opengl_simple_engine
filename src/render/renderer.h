#ifndef RENDERER_H
#define RENDERER_H

#include "core/common.h"
#include "render/buffers.h"
#include "render/vertex_array_object.h"
#include "render/shader.h"
#include "render/texture.h"

class Scene;

class Renderer {
public:
    Renderer(GLFWwindow* inWindow);

    void Init();
    void Terminate();
    void Resize(int windowWidth, int windowHeight);

    void Render(Scene* scene);

private:
    GLFWwindow* window;

    float windowWidth = 1280;
    float windowHeight = 720;
    
    glm::mat4 projectionMatr{};

    static void GlErrorCallback(int error, const char* description);

    VertexArrayObject* vaoCube;
    VertexBuffer* vBufferCube;
    Shader* cubeShader;
    Texture* texture;
    glm::mat4 cubeTrf;
};

#endif