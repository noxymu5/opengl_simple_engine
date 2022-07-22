#include <iostream>

#include "common.h"
#include "camera.h"

#include "application_cube_fall.h"

int width = 1280;
int height = 720;

ApplicationBase* app;

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void windowSizeCallback(GLFWwindow* window, int windowWidth, int windowHeight) {
    glViewport(0, 0, windowWidth, windowHeight);
    width = windowWidth;
    height = windowHeight;

    app->UpdateScreenSize(width, height);
}

int main()
{
    stbi_set_flip_vertically_on_load(true);

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

    glfwSetWindowSizeCallback(window, windowSizeCallback);

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Camera* camera = Camera::GetCamera();
    camera->Init(window, width / 2, height / 2);

    app = new ApplicationCubeFall(window, width, height);

    app->Init();
    float lastTime = 0;
    while(!glfwWindowShouldClose(window)) {
        float currTime = glfwGetTime();
        float deltaTime = currTime - lastTime;
        lastTime = currTime;

        camera->UpdateCamera(deltaTime);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        app->ExecuteLoop(deltaTime);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}