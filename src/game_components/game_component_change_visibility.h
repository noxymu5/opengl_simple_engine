#ifndef GAME_COMPONENT_CHANGE_VISIBILITY_H
#define GAME_COMPONENT_CHANGE_VISIBILITY_H

#include "game_components/game_component.h"
#include "game_components/game_component_geometry.h"

class GameComponentChangeVisibility : public GameComponent {
public:
    INIT_COMPONENT(GameComponentChangeVisibility)

    GameComponentChangeVisibility(GameObject* owner) : GameComponent(owner) {}

    virtual void Init() override;
    virtual void Update(float dt) override;
private:
    GameComponentGeometry* geom;
};

#endif