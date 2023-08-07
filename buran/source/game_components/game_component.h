#pragma once

#include <string>

#include "scene/game_object.h"

#define INIT_COMPONENT(type) static std::string Name() { return #type; }

class GameComponent {
public:
    GameComponent(GameObject* inOwner) : owner(inOwner) {}

    virtual void Init() {}
    virtual void Update(float dt) {}

protected:
    GameObject* owner;
};