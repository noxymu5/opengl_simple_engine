#include "application.h"

#include <glbinding/glbinding.h>
#include <glbinding/gl/gl.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include "core/asserts.h"
#include "core/logging.h"

#include "application/application_arguments.h"
#include "resource_system/resource_system.h"
#include "render/materials/material_system.h"
#include "input/input_system.h"
#include "render/renderer.h"
#include "scene/scene_factory/scene_factory.h"

static Application* appInstance = nullptr;

static void GlResizeCallback(GLFWwindow* window, int windowWidth, int windowHeight) {
    appInstance->Resize(window, windowWidth, windowHeight);
}

Application::Application() { appInstance = this; }

void Application::Init(ApplicationArguments args) {
    stbi_set_flip_vertically_on_load(true);

    CreateWindow();

    sceneFactory = new SceneFactory();
    RegisterComponents(sceneFactory);

    inputSystem = InputSystem::Create(window);

    resSystem = new ResourceSystem(args.GetArgument(ArgumentType::RESOURCES_ROOT));
    matSystem = new MaterialSystem(resSystem);

    renderer = new Renderer(window);
    renderer->Resize(windowWidth, windowHeight);
    renderer->Init();

    currentScene = sceneFactory->CreateScene(args);

    renderer->SetupForScene(currentScene);
}

void Application::Terminate() {
    renderer->Terminate();
}

void Application::Execute() {
    double lastTime = 0;

    while (IsWindowOpen())
    {
        double currTime = glfwGetTime();
        double deltaTime = currTime - lastTime;
        lastTime = currTime;

        currentScene->Update(static_cast<float>(deltaTime));
        renderer->Render(currentScene);

        inputSystem->ProcessInput();
    }
}

void Application::Resize(GLFWwindow* window, int width, int height) {
    windowHeight = height;
    windowWidth = width;

    gl::glViewport(0, 0, windowWidth, windowHeight);
    renderer->Resize(windowWidth, windowHeight);
}

void Application::CreateWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback(GlErrorCallback);

    window = glfwCreateWindow(windowWidth, windowHeight, "Buran", NULL, NULL);
    if (window == NULL) {
        ASSERT_FAIL("Failed to create GLFW window")
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glbinding::initialize(glbinding::GetProcAddress());

    glfwSetWindowSizeCallback(window, GlResizeCallback);

    gl::glViewport(0, 0, windowWidth, windowHeight);
}

bool Application::IsWindowOpen() const {
    return !static_cast<bool>(glfwWindowShouldClose(window));
}

void Application::GlErrorCallback(int error, const char* description) {
    LOG("Error %d: %s", error, description)
    ASSERT_FAIL(description)
}