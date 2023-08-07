#include "game_component_fly_camera.h"

#include <GLFW/glfw3.h>

#include "core/glm_declarations.h"
#include <glm/gtx/quaternion.hpp>
#include "input/input_system.h"
#include "core/logging.h"

#include "game_components/serializers/game_component_serializer.h"

BEGIN_SERIALIZER(GameComponentFlyCamera)
EXPOTR_FIELD(movementSpeed, float)
EXPOTR_FIELD(movementSpeedScale, float)
END_SERIALIZER(GameComponentFlyCamera)

void GameComponentFlyCamera::Update(float dt) {
    UpdateSpeed();
    UpdateDirection();
    UpdatePosition(dt);
}

void GameComponentFlyCamera::UpdateSpeed() {
    if (InputSystem::IsKeyDown(GLFW_KEY_LEFT_SHIFT)) {
        currentSpeed = movementSpeed * movementSpeedScale;
    } else {
        currentSpeed = movementSpeed;
    }
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

    owner->GetTransform().SetEulerAngles(glm::vec3(pitch, yaw, 0));
}

void GameComponentFlyCamera::UpdatePosition(float dt) {
    glm::vec3 movementVector(0);

    glm::vec3 forward = owner->GetTransform().Forward();
    glm::vec3 right = owner->GetTransform().Right();
    glm::vec3 up = owner->GetTransform().Up();

    if (InputSystem::IsKeyDown(GLFW_KEY_W)) {
        movementVector += forward * dt * currentSpeed;
    }
    
    if (InputSystem::IsKeyDown(GLFW_KEY_S)) {
        movementVector -= forward * dt * currentSpeed;
    }
    
    if (InputSystem::IsKeyDown(GLFW_KEY_A)) {
        movementVector += right * dt * currentSpeed;
    }
    
    if (InputSystem::IsKeyDown(GLFW_KEY_D)) {
        movementVector -= right * dt * currentSpeed;
    }
    
    if (InputSystem::IsKeyDown(GLFW_KEY_E)) {
        movementVector += up * dt * currentSpeed;
    }

    if (InputSystem::IsKeyDown(GLFW_KEY_Q)) {
        movementVector -= up * dt * currentSpeed;
    }

    if (glm::length(movementVector) == 0) {
        return;
    }

    owner->GetTransform().Translate(movementVector);
}