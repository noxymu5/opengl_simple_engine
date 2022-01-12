#include <iostream>

#include "common.h"
#include "camera.h"

#include "application_cube_fall.h"

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

int main()
{
    stbi_set_flip_vertically_on_load(true);
    const float width = 800;
    const float height = 600;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(width, height, "Test window", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Camera* camera = Camera::GetCamera();
    camera->Init(window, width / 2, height / 2);

    //Create application
    ApplicationBase* app = new ApplicationCubeFall(window, width, height);
    //Create application end

    // Texture texture("../assets/textures/test_tex.png", GL_RGBA);
    // Shader shader("../shaders/simple_shader.glsl");

    // VertexArrayObject vao;
    // vao.Bind();
    //     VertexBuffer vbo(HELPERS::planeVertexData, sizeof(HELPERS::planeVertexData));
    //     IndexBuffer ebo(HELPERS::planeIndexData, sizeof(HELPERS::planeIndexData));

    //     shader.BindVertexAttributes();
    // vao.UnBind();

    // glm::mat4 proj = glm::perspective(glm::radians(45.0f), width/height, 0.1f, 100.0f);

    app->Init();
    float lastTime = 0;
    while(!glfwWindowShouldClose(window)) {
        float currTime = glfwGetTime();
        float deltaTime = currTime - lastTime;
        lastTime = currTime;

        camera->UpdateCamera(deltaTime);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // shader.Use();
        // vao.Bind();
        //     glm::mat4 mvp = proj * camera->GetCameraMatr() * glm::mat4(1.0f);
        //     shader.SetUniform("trf", &mvp);

        //     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        // vao.UnBind();

        app->ExecuteLoop(deltaTime);

        glfwPollEvents();
        glfwSwapBuffers(window);
    } 

    glfwTerminate();
    return 0;
}