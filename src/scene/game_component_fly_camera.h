#ifndef GAME_COMPONENT_FLYCAMERA_H
#define GAME_COMPONENT_FLYCAMERA_H

#include "scene/game_component.h"

class GameComponentFlyCamera : public GameComponent {
public:
    GameComponentFlyCamera(GameObject* owner) : GameComponent(owner) {
        position = owner->GetPos();
        forward = owner->GetTransform().Forward();
    }

    virtual void Update(float dt) override;

private:
    const float maxPitch = 90;
    const float minPitch = -90;
    const float movementSpeed = 5;
    const float mouseSensitivity = 0.1;

    float lastMouseX;
    float lastMouseY;

    float yaw;
    float pitch;

    glm::vec3 position{0};
    glm::vec3 forward{0, 0, 1};

    void UpdateDirection();
    void UpdatePosition(float dt, glm::vec3 right, glm::vec3 up);
};

#endif