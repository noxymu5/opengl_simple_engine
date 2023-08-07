#pragma once

struct GLFWwindow;

class InputSystem {
public:
    InputSystem(GLFWwindow* inWindow);

    static InputSystem* Create(GLFWwindow* window);
    static InputSystem* Get();

    GLFWwindow* GetWindow();

    static void GetCursorPos(double* posX, double* posY);
    static bool IsKeyDown(int key);
    static bool IsKeyPressed(int key);
    static bool IsKeyReleased(int key);

private:
    GLFWwindow* window = nullptr;
};