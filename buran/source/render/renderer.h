#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <glm/vec4.hpp>

#include "render/light_data.h"
#include "render/texture/texture_to_screen_dumper.h"
#include "core/glm_declarations.h"

struct GLFWwindow;
class Scene;
class FrameBuffer;
class RenderBufferObject;
class Texture;

class Skybox;

class Renderer {
public:
    Renderer(GLFWwindow* inWindow);

    void Init();
    void SetupForScene(Scene* scn);
    void Terminate();
    void Resize(int windowWidth, int windowHeight);

    void Render(Scene* scene);

private:
    GLFWwindow* window = nullptr;

    int windowWidth = 1280;
    int windowHeight = 720;
    
    glm::mat4 projectionMatr{};

    FrameBuffer* frameBuffer = nullptr;
    RenderBufferObject* rbo = nullptr;
    Texture* frameBufferOutput = nullptr;
    TextureToScreenDumper dumper;

    Skybox* skybox = nullptr;

    glm::vec4 skyColor = {0, 0, 0, 1};

    SceneLightsData* PrepareLightData(Scene* scene);
    static void GlErrorCallback(int error, const char* description);
};

#endif