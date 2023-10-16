#include "renderer.h"

#include <glbinding/gl/gl.h>
#include <GLFW/glfw3.h>

#include "core/logging.h"
#include "core/asserts.h"
#include "scene/scene.h"
#include "scene/camera.h"

#include "game_components/game_component_geometry.h"
#include "render_context.h"

#include "render/buffers.h"
#include "render/primitives/render_buffer_object.h"

#include "render/texture/texture.h"

#include "render/cube_map/skybox.h"

Renderer::Renderer(GLFWwindow* inWindow) : window(inWindow) {};

void Renderer::Init() {
    gl::glEnable(gl::GL_DEPTH_TEST);
    gl::glEnable(gl::GL_CULL_FACE);
    gl::glCullFace(gl::GL_BACK);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
}

void Renderer::SetupForScene(Scene* scn) {
    SceneSkyConfig* config = scn->GetSkyConfig();

    if (skybox != nullptr) {
        delete(skybox);
    }

    if (!config->skyTexture.empty()) {
        skybox = new Skybox(config->skyTexture);
    } else {
        skyColor = config->skyColor;
    }
}

void Renderer::Terminate() {
    glfwTerminate();
}

void Renderer::Render(Scene* scene) {
    frameBuffer->Bind();
    gl::glEnable(gl::GL_DEPTH_TEST);

    gl::glClearColor(skyColor.x, skyColor.y, skyColor.z, skyColor.w);
    gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);

    Camera* cam = scene->GetCamera();
    Transform camTrf = cam->GetTransform();
    glm::vec3 camPos = camTrf.GetPosition();
    
    glm::mat4 viewProj = projectionMatr * cam->GetViewMatrix();

    std::vector<GameObject*> objects = scene->GetGameObjects();

    RenderContext ctx;
    ctx.view = cam->GetViewMatrix();
    ctx.proj = projectionMatr;
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

    if (skybox != nullptr) {
        gl::glDepthFunc(gl::GL_LEQUAL);
        gl::glDisable(gl::GL_CULL_FACE);

        skybox->Draw(ctx);

        gl::glDepthFunc(gl::GL_LESS);
        gl::glEnable(gl::GL_CULL_FACE);
    }

    frameBuffer->Unbind();

    gl::glDisable(gl::GL_DEPTH_TEST);

    gl::glClearColor(1, 1, 1, 1);
    gl::glClear(gl::GL_COLOR_BUFFER_BIT);

    dumper.DumpToScreen(frameBufferOutput);

    glfwSwapBuffers(window);
}

void Renderer::Resize(int width, int height) {
    windowHeight = height;
    windowWidth = width;

    projectionMatr = glm::perspective(glm::radians(45.0f), (float)windowWidth/(float)windowHeight, 0.1f, 500.0f);

    if (rbo != nullptr) {
        delete(rbo);
    }

    if (frameBufferOutput != nullptr) {
        delete(frameBufferOutput);
    }

    rbo = new RenderBufferObject(windowWidth, windowHeight);
    frameBufferOutput = new Texture(windowWidth, windowHeight, nullptr);

    frameBuffer = new FrameBuffer(FrameBufferBindType::READ_AND_WRITE);
    frameBuffer->Bind();
    
    frameBuffer->Attach(frameBufferOutput, FrameBufferAttachmentType::COLOR);
    frameBuffer->Attach(rbo, FrameBufferAttachmentType::DEPTH_STENCIL);

    frameBuffer->Validate();

    frameBuffer->Unbind();
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