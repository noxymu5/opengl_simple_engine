#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "render/light_data.h"
#include "render/texture_to_screen_dumper.h"
#include "core/glm_declarations.h"

class GLFWwindow;
class Scene;
class FrameBuffer;
class RenderBufferObject;
class Texture;

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

    FrameBuffer* frameBuffer = nullptr;
    RenderBufferObject* rbo = nullptr;
    Texture* frameBufferOutput = nullptr;
    TextureToScreenDumper dumper;

    SceneLightsData* PrepareLightData(Scene* scene);
    static void GlErrorCallback(int error, const char* description);
};

#endif