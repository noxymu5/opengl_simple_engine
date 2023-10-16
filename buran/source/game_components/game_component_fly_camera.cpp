#include "game_component_fly_camera.h"

#include "core/glm_declarations.h"
#include <glm/gtx/quaternion.hpp>

#include "input/input_system.h"
#include "input/key_codes.h"
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
    if (InputSystem::IsKeyPressed(KeyCode::KB_LEFT_SHIFT)) {
        currentSpeed = movementSpeed * movementSpeedScale;
    } else {
        currentSpeed = movementSpeed;
    }
}

void GameComponentFlyCamera::UpdateDirection() {
    yaw -= InputSystem::GetAxisRaw(AxisType::MS_HORIZONTAL) * mouseSensitivity;
    pitch += InputSystem::GetAxisRaw(AxisType::MS_VERTICAL) * mouseSensitivity;
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

    movementVector += forward * dt * InputSystem::GetAxis(AxisType::KB_SYM_VERTICAL) * currentSpeed;
    movementVector -= right * dt * InputSystem::GetAxis(AxisType::KB_SYM_HORIZONTAL) * currentSpeed;

    if (InputSystem::IsKeyPressed(KeyCode::KB_E)) {
        movementVector += up * dt * currentSpeed;
    }

    if (InputSystem::IsKeyPressed(KeyCode::KB_Q)) {
        movementVector -= up * dt * currentSpeed;
    }

    if (glm::length(movementVector) == 0) {
        return;
    }

    owner->GetTransform().Translate(movementVector);
}