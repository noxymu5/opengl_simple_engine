#include "renderer.h"

#include "core/logging.h"
#include "core/asserts.h"
#include "scene/scene.h"
#include "scene/camera.h"

#include "core/helpers.h"

Renderer::Renderer(GLFWwindow* inWindow) : window(inWindow) {};

void Renderer::Init() {
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    texture = new Texture("C:\\home_projects\\cpp_proj\\opengl_simple_engine\\assets\\textures\\container.jpg", GL_RGB);
    cubeShader = new Shader("C:\\home_projects\\cpp_proj\\opengl_simple_engine\\shaders\\simple_lit_shader.glsl");
    
    vaoCube = new VertexArrayObject();
    vaoCube->Bind();
        vBufferCube = new VertexBuffer(HELPERS::cubeVertexDataUvNormals, sizeof(HELPERS::cubeVertexDataUvNormals));
        cubeShader->BindVertexAttributes();
    vaoCube->UnBind();
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

    glm::mat4 viewProj = projectionMatr * camTrf.Get();

    for(int idx = 0; idx < 4; ++idx) {
        cubeTrf[idx][idx] = 1;
    }

    vaoCube->Bind();
        cubeShader->Use();
        cubeShader->SetUniform("viewProj", viewProj);
        cubeShader->SetUniform("model", cubeTrf);
        cubeShader->SetUniform("ulightColor", glm::vec3(1.0f));
        cubeShader->SetUniform("ulightPos", glm::vec3(0, 0, 4));
        cubeShader->SetUniform("uViewPos", cam->GetPos());
        
        glDrawArrays(GL_TRIANGLES, 0, 36);
    vaoCube->UnBind();

    glfwSwapBuffers(window);
}

void Renderer::Resize(int width, int height) {
    windowHeight = height;
    windowWidth = width;

    projectionMatr = glm::perspective(glm::radians(45.0f), windowWidth/windowHeight, 0.1f, 100.0f);
}