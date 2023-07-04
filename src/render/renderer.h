#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "render/shader.h"
#include "render/light_data.h"

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

    Shader* mainModelShader;

    std::vector<LightData*> PrepareLightData(Scene* scene);
};

#endif