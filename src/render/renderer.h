#ifndef RENDERER_H
#define RENDERER_H

#include "render/buffers.h"
#include "render/vertex_array_object.h"
#include "render/shader.h"
#include "render/texture.h"

#include "core/glm_declarations.h"

class GLFWwindow;
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
    IndexBuffer* iBuffer;
    Shader* mainModelShader;
    glm::mat4 cubeTrf;
    int count;
};

#endif