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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Camera* cam = scene->GetCamera();
    Transform camTrf = cam->GetTransform();
    glm::vec3 camPos = camTrf.GetPosition();
    
    glm::mat4 viewProj = projectionMatr * cam->GetViewMatrix();

    std::vector<GameObject*> objects = scene->GetGameObjects();
    
    RenderContext ctx;
    ctx.viewProj = viewProj;
    ctx.viewPos = camPos;
    ctx.lightData = PrepareLightData(scene);

    for(auto gameObject : objects) {
        if (!gameObject->IsEnabled()) {
            continue;
        }

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

    projectionMatr = glm::perspective(glm::radians(45.0f), windowWidth/windowHeight, 0.1f, 500.0f);
}

SceneLightsData* Renderer::PrepareLightData(Scene* scene) {
    std::vector<Light*> lights = scene->GetLights();

    SceneLightsData* lightData = new SceneLightsData();
    for (int idx = 0; idx < lights.size(); ++idx) {

        Light* light = lights[idx];

        switch (light->type)
        {
        case LIGHT_TYPE::POINT:
            {
                PointLightData* pointLightData = new PointLightData();
                pointLightData->color = light->color;
                pointLightData->distance = light->distance;
                pointLightData->position = light->GetPos();

                lightData->pointLights.push_back(pointLightData);
            }
            break;
        case LIGHT_TYPE::DIRECTIONAL:
            if (lightData->directionalLight != nullptr) {
                break;
            }

            {
                DirectionalLightData* directionalLightData = new DirectionalLightData();
                directionalLightData->color = light->color;
                directionalLightData->direction = light->GetTransform().Forward();

                lightData->directionalLight = directionalLightData;
            }
            break;
        case LIGHT_TYPE::SPOT_LIGHT:
            {
                SpotLightData* spotLightData = new SpotLightData();
                spotLightData->color = light->color;
                spotLightData->direction = light->GetTransform().Forward();
                spotLightData->cutoffAngle = light->cutoffAngle;
                spotLightData->position = light->GetPos();
                spotLightData->radius = light->distance;

                lightData->spotLights.push_back(spotLightData);
            }
            break;
        default:
            ASSERT_FAIL("Unknown light type")
            break;
        }
    }

    return lightData;
}