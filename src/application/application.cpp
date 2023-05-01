#include "application.h"

#include "core/common.h"

#include "stb_image.h"

#include "core/asserts.h"
#include "core/logging.h"

#include "input/input_system.h"
#include "render/renderer.h"
#include "scene/scene.h"

static Application* appInstance;

static void GlResizeCallback(GLFWwindow* window, int windowWidth, int windowHeight) {
    appInstance->Resize(window, windowWidth, windowHeight);
}

Application::Application() { appInstance = this; }

void Application::Init() {
    stbi_set_flip_vertically_on_load(true);

    CreateWindow();

    inputSystem = InputSystem::Create(window);
    currentScene = new Scene();
    renderer = new Renderer(window);
    renderer->Resize(windowWidth, windowHeight);
    renderer->Init();

    glewInit();
}

void Application::Terminate() {
    renderer->Terminate();
}

void Application::Execute() {
    float lastTime = 0;

    while (IsWindowOpen())
    {
        float currTime = glfwGetTime();
        float deltaTime = currTime - lastTime;
        lastTime = currTime;

        // LOG("delta time %f", deltaTime)

        currentScene->Update(deltaTime);
        renderer->Render(currentScene);

        glfwPollEvents();
    }
}

void Application::Resize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, windowWidth, windowHeight);
    windowHeight = height;
    windowWidth = width;

    renderer->Resize(width, height);
}

void Application::CreateWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(GlErrorCallback);

    window = glfwCreateWindow(windowWidth, windowHeight, "Test window", NULL, NULL);
    if (window == NULL) {
        ASSERT_FAIL("Failed to create GLFW window")
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glewInit();

    glfwSetWindowSizeCallback(window, GlResizeCallback);

    glViewport(0, 0, windowWidth, windowHeight);
}

bool Application::IsWindowOpen() const {
    return !static_cast<bool>(glfwWindowShouldClose(window));
}

void Application::GlErrorCallback(int error, const char* description) {
    LOG("Error %d: %s", error, description)
    ASSERT_FAIL(description)
}