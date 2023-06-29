#include "renderer.h"

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "core/logging.h"
#include "core/asserts.h"
#include "scene/scene.h"
#include "scene/camera.h"

#include "core/helpers.h"
#include "game_components/game_component_geometry.h"

Renderer::Renderer(GLFWwindow* inWindow) : window(inWindow) {};

void Renderer::Init() {
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    mainModelShader = new Shader("simple_shader.glsl");
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
    
    for(auto gameObject : objects) {
        GameComponentGeometry* comp = gameObject->TryGet<GameComponentGeometry>();
        if (comp == nullptr || !comp->IsVisible()) {
            continue;
        }

        comp->StartDraw();

        mainModelShader->Use();
        mainModelShader->BindVertexAttributes();

        mainModelShader->SetUniform("trf", viewProj * gameObject->GetTransform().Get());

        // mainModelShader->SetUniform("viewProj", viewProj);
        // mainModelShader->SetUniform("ulightColor", glm::vec3(1.0f));
        // mainModelShader->SetUniform("ulightPos", glm::vec3(0, 3, -3));
        // mainModelShader->SetUniform("uViewPos", cam->GetPos());

        // mainModelShader->SetUniform("model", gameObject->GetTransform().Get());
        comp->EndDraw();
    }

    glfwSwapBuffers(window);
}

void Renderer::Resize(int width, int height) {
    windowHeight = height;
    windowWidth = width;

    projectionMatr = glm::perspective(glm::radians(45.0f), windowWidth/windowHeight, 0.1f, 100.0f);
}