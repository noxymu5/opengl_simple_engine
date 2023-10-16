#pragma once

#include <string>
#include <vector>

#include "input/devices/input_device_manager.h"

struct GLFWwindow;
enum class KeyCode;

class InputSystem {
public:
    InputSystem(GLFWwindow* inWindow);

    static InputSystem* Create(GLFWwindow* window);
    static InputSystem* Get();

    GLFWwindow* GetWindow();
    void ProcessInput();

    static void GetCursorPos(double* posX, double* posY);

    static bool IsKeyDown(KeyCode key);
    static bool IsKeyPressed(KeyCode key);
    static bool IsKeyReleased(KeyCode key);

    static float GetAxis(AxisType type);
    static float GetAxisRaw(AxisType type);

    static bool IsInputDown(std::string input);
    static bool IsInputPressed(std::string input);
    static bool IsInputReleased(std::string input);

private:
    GLFWwindow* window = nullptr;

    std::vector<InputDeviceManager*> deviceManagers;

    bool CheckKeyState(KeyCode key, KeyState desiredState);
    float GetAxisInternal(AxisType type);
    float GetAxisRawInternal(AxisType type);
};