#include "game_component_fly_camera.h"

#include <GLFW/glfw3.h>

#include "core/glm_declarations.h"
#include "input/input_system.h"
#include "core/logging.h"

#include "game_components/serializers/game_component_serializer.h"

BEGIN_SERIALIZER(GameComponentFlyCamera)
END_SERIALIZER(GameComponentFlyCamera)

void GameComponentFlyCamera::Update(float dt) {
    // UpdateDirection();

    // glm::vec3 right = glm::cross(glm::vec3(0, 1, 0), forward);
    // glm::vec3 up = glm::cross(forward, right);

    UpdatePosition(dt, glm::vec3(0), glm::vec3(0));

    // owner->SetTransform(glm::lookAt(position, position + forward, up));
}

void GameComponentFlyCamera::UpdateDirection() {
    double currMouseX, currMouseY;
    InputSystem::GetCursorPos(&currMouseX, &currMouseY);

    double mouseDiffX = lastMouseX - currMouseX;
    double mouseDiffY = currMouseY - lastMouseY;
    
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

    forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward.y = sin(glm::radians(pitch));
    forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}

void GameComponentFlyCamera::UpdatePosition(float dt, glm::vec3 right, glm::vec3 up) {
    glm::vec3 movementVector(0);

    glm::vec3 forward = owner->GetTransform().Forward();
    right = owner->GetTransform().Right();
    up = owner->GetTransform().Up();

    if (InputSystem::IsKeyDown(GLFW_KEY_W)) {
        movementVector += forward * dt * movementSpeed;
    }
    
    if (InputSystem::IsKeyDown(GLFW_KEY_S)) {
        movementVector -= forward * dt * movementSpeed;
    }
    
    if (InputSystem::IsKeyDown(GLFW_KEY_A)) {
        movementVector += right * dt * movementSpeed;
    }
    
    if (InputSystem::IsKeyDown(GLFW_KEY_D)) {
        movementVector -= right * dt * movementSpeed;
    }
    
    if (InputSystem::IsKeyDown(GLFW_KEY_Q)) {
        movementVector -= up * dt * movementSpeed;
    }
    
    if (InputSystem::IsKeyDown(GLFW_KEY_E)) {
        movementVector += up * dt * movementSpeed;
    }

    if (glm::length(movementVector) == 0) {
        return;
    }

    owner->GetTransform().Translate(movementVector);
}