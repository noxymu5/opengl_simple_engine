#include "renderer.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "core/logging.h"
#include "core/asserts.h"
#include "scene/scene.h"
#include "scene/camera.h"

#include "game_components/game_component_geometry.h"
#include "render_context.h"

Renderer::Renderer(GLFWwindow* inWindow) : window(inWindow) {};

void Renderer::Init() {
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Renderer::Terminate() {
    glfwTerminate();
}

void Renderer::Render(Scene* scene) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Camera* cam = scene->GetCamera();
    Transform camTrf = cam->GetTransform();
    glm::vec3 camPos = camTrf.GetPosition();
    
    glm::mat4 viewProj = projectionMatr * cam->GetViewMatrix();

    std::vector<GameObject*> objects = scene->GetGameObjects();
    
    RenderContext ctx;
    ctx.viewProj = viewProj;
    ctx.viewPos = camPos;
    ctx.lightsData = PrepareLightData(scene);

    for(auto gameObject : objects) {
        GameComponentGeometry* comp = gameObject->TryGet<GameComponentGeometry>();
        if (comp == nullptr || !comp->IsVisible()) {
            continue;
        }

        ctx.model = gameObject->GetTransform().Get();
        comp->Draw(ctx);
    }

    glfwSwapBuffers(window);
}

void Renderer::Resize(int width, int height) {
    windowHeight = height;
    windowWidth = width;

    projectionMatr = glm::perspective(glm::radians(45.0f), windowWidth/windowHeight, 0.1f, 100.0f);
}

std::vector<LightData*> Renderer::PrepareLightData(Scene* scene) {
    std::vector<Light*> lights = scene->GetLights();

    std::vector<LightData*> datas;

    for (int idx = 0; idx < lights.size(); ++idx) {
        LightData* data = new LightData();

        Light* light = lights[idx];
        data->color = light->color;
        data->type = light->type;
        data->position = light->GetPos();
        data->direction = light->GetTransform().Forward();
        data->distance = light->distance;

        datas.push_back(data);
    }

    return datas;
}