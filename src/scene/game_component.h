#ifndef GAME_COMPONENT
#define GAME_COMPONENT

#include "scene/game_object.h"

class GameComponent {
public:
    GameComponent(GameObject* inOwner) : owner(inOwner) {}

    virtual void Update(float dt) {};

protected:
    GameObject* owner;
};

#endif