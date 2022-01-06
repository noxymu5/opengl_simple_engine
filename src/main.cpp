#include <iostream>

#include "common.h"
#include "camera.h"

#include "application_cube_fall.h"

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

int main()
{
    const float width = 800;
    const float height = 600;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

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

    app->Init();
    float lastTime = 0;
    while(!glfwWindowShouldClose(window)) {
        float currTime = glfwGetTime();
        float deltaTime = currTime - lastTime;
        lastTime = currTime;

        camera->UpdateCamera(deltaTime);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        app->ExecuteLoop(deltaTime);

        glfwPollEvents();
        glfwSwapBuffers(window);
    } 

    glfwTerminate();
    return 0;
}