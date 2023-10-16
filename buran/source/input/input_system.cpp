#include "input/input_system.h"

#include <GLFW/glfw3.h>

#include "input/devices/input_device_manager_xinput.h"
#include "input/devices/input_device_manager_keyboard.h"
#include "input/devices/input_device_manager_mouse.h"

#include "input/key_codes.h"
#include "core/asserts.h"

static InputSystem* instance;

InputSystem::InputSystem(GLFWwindow* inWindow) : window(inWindow) {
    deviceManagers.push_back(new InputDeviceManagerXinput(window));
    deviceManagers.push_back(new InputDeviceManagerKeyboard(window));
    deviceManagers.push_back(new InputDeviceManagerMouse(window));
};

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

bool InputSystem::CheckKeyState(KeyCode key, KeyState desiredState) {
    KeyState keyState;
    bool isKeyFound = false;

    for (auto& deviceManager : deviceManagers) {
        if (deviceManager->CheckKey(key, keyState)) {
            isKeyFound = true;
            break;
        }
    }

    return isKeyFound && keyState == desiredState;
}

float InputSystem::GetAxisInternal(AxisType type) {
    float axisValue = .0f;

    for (auto& deviceManager : deviceManagers) {
        if (deviceManager->GetAxis(type, axisValue)) {
            break;
        }
    }
    return axisValue;
}

float InputSystem::GetAxisRawInternal(AxisType type) {
    float axisValue = .0f;

    for (auto& deviceManager : deviceManagers) {
        if (deviceManager->GetAxisRaw(type, axisValue)) {
            break;
        }
    }
    return axisValue;
}

void InputSystem::ProcessInput() {
    for (auto& deviceManager : deviceManagers) {
        deviceManager->ProcessInput();
    }
}

void InputSystem::GetCursorPos(double* posX, double* posY) {
    glfwGetCursorPos(instance->GetWindow(), posX, posY);
}

bool InputSystem::IsKeyDown(KeyCode key) {
    return instance->CheckKeyState(key, KeyState::HELD);
}

bool InputSystem::IsKeyPressed(KeyCode key) {
    return instance->CheckKeyState(key, KeyState::PRESSED);
}

bool InputSystem::IsKeyReleased(KeyCode key) {
    return instance->CheckKeyState(key, KeyState::RELEASED);
}

float InputSystem::GetAxis(AxisType type) {
    return instance->GetAxisInternal(type);
}

float InputSystem::GetAxisRaw(AxisType type) {
    return instance->GetAxisRawInternal(type);
}

bool InputSystem::IsInputDown(std::string input) {
    return false;
}

bool InputSystem::IsInputPressed(std::string input) {
    return false;
}

bool InputSystem::IsInputReleased(std::string input) {
    return false;
}