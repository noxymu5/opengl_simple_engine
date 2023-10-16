#pragma once

#include "game_components/game_component.h"

class GameComponentFlyCamera : public GameComponent {
public:
    INIT_COMPONENT(GameComponentFlyCamera)

    float movementSpeed = 5;
    float movementSpeedScale = 3;

    GameComponentFlyCamera(GameObject* owner) : GameComponent(owner) {
        position = owner->GetPos();
        forward = owner->GetTransform().Forward();
    }

    virtual void Update(float dt) override;

private:
    const float maxPitch = 90;
    const float minPitch = -90;
    const float mouseSensitivity = 1.0f;

    double yaw = 0;
    double pitch = 0;

    float currentSpeed = 0;
    glm::vec3 position{0};
    glm::vec3 forward{0, 0, 1};

    void UpdateSpeed();
    void UpdateDirection();
    void UpdatePosition(float dt);
};