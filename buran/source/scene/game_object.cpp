#include "scene/game_object.h"

#include "game_components/game_component.h"

void GameObject::Init() {
    for(auto comp : components) {
        comp.second->Init();
    }
}

void GameObject::Update(float dt) {
    UpdateImpl(dt);

    for(auto comp : components) {
        comp.second->Update(dt);
    }
}