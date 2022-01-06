#include "camera.h"

Camera::Camera() {}

Camera* Camera::GetCamera() {
    if (instance) {
        return instance;
    }

    instance = new Camera();
    return instance;
}

void Camera::Init(GLFWwindow *inWindow, float initialMouseX, float initialMouseY) {
    window = inWindow;
    lastMouseX = initialMouseX;
    lastMouseY = initialMouseY;
}

Camera::~Camera() {
}

glm::mat4 Camera::GetCameraMatr() {
    return glm::lookAt(position, position + cameraForward, up);
}

void Camera::UpdateCamera(float dt) {
    glm::vec3 direction = UpdateDirection();
    cameraForward = glm::normalize(direction);
    
    right = glm::cross(cameraForward, glm::vec3(0.0, 1.0, 0.0));
    up = glm::cross(right, cameraForward);

    UpdatePosition(dt);
}

glm::vec3 Camera::UpdateDirection() {
    double currMouseX, currMouseY;
    glfwGetCursorPos(window, &currMouseX, &currMouseY);

    double mouseDiffX = currMouseX - lastMouseX;
    double mouseDiffY = lastMouseY - currMouseY;
    
    lastMouseX = currMouseX;
    lastMouseY = currMouseY;

    yaw += mouseDiffX * mouseSensitivity;
    pitch += mouseDiffY * mouseSensitivity;
    if (pitch > maxPitch) {
        pitch  = maxPitch;
    }
    else if (pitch < minPitch) {
        pitch = minPitch;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    return direction;
}

void Camera::UpdatePosition(float dt) {
    glm::vec3 movementVector(0);

    if (IsKeyPressed(GLFW_KEY_W)) {
        movementVector += cameraForward * dt * movementSpeed;
    }
    
    if (IsKeyPressed(GLFW_KEY_S)) {
        movementVector -= cameraForward * dt * movementSpeed;
    }
    
    if (IsKeyPressed(GLFW_KEY_A)) {
        movementVector -= right * dt * movementSpeed;
    }
    
    if (IsKeyPressed(GLFW_KEY_D)) {
        movementVector += right * dt * movementSpeed;
    }
    
    if (IsKeyPressed(GLFW_KEY_Q)) {
        movementVector -= glm::vec3(0.0, 1.0, 0.0) * dt * movementSpeed;
    }
    
    if (IsKeyPressed(GLFW_KEY_E)) {
        movementVector += glm::vec3(0.0, 1.0, 0.0) * dt * movementSpeed;
    }

    float length = glm::length(movementVector);
    if (length > movementSpeed) {
        movementVector = glm::normalize(movementVector);
        movementVector *= movementSpeed;
    }

    position += movementVector;
}

bool Camera::IsKeyPressed(int key) {
    int state = glfwGetKey(window, key);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}