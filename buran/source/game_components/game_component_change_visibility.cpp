#include "game_component_change_visibility.h"

#include "input/input_system.h"
#include "input/key_codes.h"

void GameComponentChangeVisibility::Init() {
    geom = owner->Get<GameComponentGeometry>();
}

void GameComponentChangeVisibility::Update(float dt) {
    if (InputSystem::IsKeyPressed(KeyCode::KB_C)) {
        geom->SetVisible(!geom->IsVisible());
    }
}