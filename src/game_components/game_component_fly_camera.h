#ifndef GAME_COMPONENT_FLYCAMERA_H
#define GAME_COMPONENT_FLYCAMERA_H

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
    const float mouseSensitivity = 0.1;

    float lastMouseX = 0;
    float lastMouseY = 0;

    float yaw = 0;
    float pitch = 0;

    float currentSpeed = 0;
    glm::vec3 position{0};
    glm::vec3 forward{0, 0, 1};

    void UpdateSpeed();
    void UpdateDirection();
    void UpdatePosition(float dt);
};

#endif