#ifndef CAMERA
#define CAMERA

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

class Camera
{
private:
    const float maxPitch = 90;
    const float minPitch = -90;
    const float movementSpeed = 5;
    const float mouseSensitivity = 0.1;

    GLFWwindow* window;

    float lastMouseX;
    float lastMouseY;

    float yaw;
    float pitch;

    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 right;

    glm::vec3 cameraForward;

    glm::vec3 UpdateDirection();
    void UpdatePosition(float dt);
    bool IsKeyPressed(int key);

public:
    Camera(GLFWwindow *inWindow, float initialMouseX, float initialMouseY);
    ~Camera();

    glm::mat4 GetCameraMatr();
    void UpdateCamera(float dt);
};

#endif