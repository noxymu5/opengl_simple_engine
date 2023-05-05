#include "input/input_system.h"

#include <GLFW/glfw3.h>

#include "core/asserts.h"

static InputSystem* instance;

InputSystem::InputSystem(GLFWwindow* inWindow) : window(inWindow) {};

InputSystem* InputSystem::Create(GLFWwindow* window) {
    ASSERT(instance == nullptr, "InputSystem is already created")

    instance = new InputSystem(window);
    return instance;
}

InputSystem* InputSystem::Get() {
    ASSERT(instance != nullptr, "Trying to get InputSystem before its creation")
    return instance;
}

GLFWwindow* InputSystem::GetWindow() { return window; }

void InputSystem::GetCursorPos(double* posX, double* posY) {
    glfwGetCursorPos(InputSystem::Get()->GetWindow(), posX, posY);
}

bool InputSystem::IsKeyDown(int key) {
    int state = glfwGetKey(InputSystem::Get()->GetWindow(), key);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}