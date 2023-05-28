#include "game_component_change_visibility.h"

#include "input/input_system.h"
#include <GLFW/glfw3.h>

void GameComponentChangeVisibility::Init() {
    geom = owner->Get<GameComponentGeometry>();
}

void GameComponentChangeVisibility::Update(float dt) {
    if (InputSystem::IsKeyPressed(GLFW_KEY_C)) {
        geom->SetVisible(!geom->IsVisible());
    }
}