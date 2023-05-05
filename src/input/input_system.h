#ifndef INPUT_SYSTEM_H
#define IMPUT_SYSTEM

class GLFWwindow;

class InputSystem {
public:
    InputSystem(GLFWwindow* inWindow);

    static InputSystem* Create(GLFWwindow* window);
    static InputSystem* Get();

    GLFWwindow* GetWindow();

    static void GetCursorPos(double* posX, double* posY);
    static bool IsKeyDown(int key);

private:
    GLFWwindow* window;
};

#endif