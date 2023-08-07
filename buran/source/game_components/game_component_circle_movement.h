#ifndef CIRCLE_MOVEMENT_H
#define CIRCLE_MOVEMENT_H

#include "game_components/game_component.h"

class GameComponentCircleMovement : public GameComponent {
public:
    INIT_COMPONENT(GameComponentCircleMovement)

    float rotationSpeed = 1;
    float radius = 3;
    float height;
    
    GameComponentCircleMovement(GameObject* owner) : GameComponent(owner) {}

    virtual void Update(float dt) override;
private:
    float angle;

};

#endif