#include "scene/game_object.h"

#include "scene/game_component.h"

void GameObject::Update(float dt) {
    UpdateImpl(dt);

    for(int idx = 0; idx < components.size(); idx += 1) {
        components[idx]->Update(dt);
    }
}