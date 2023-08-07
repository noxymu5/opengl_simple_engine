#pragma once

#include <string>

#include "resource_system/resource/resource_mesh.h"

#include "game_components/game_component.h"
#include "render/mesh/mesh.h"
#include "render/render_context.h"

class GameComponentGeometry : public GameComponent {
public:
    INIT_COMPONENT(GameComponentGeometry)

    GameComponentGeometry(GameObject* owner) : GameComponent(owner) {}

    virtual void Init() override;

    void Draw(RenderContext ctx);

    void SetVisible(bool val) { isVisible = val; }
    bool IsVisible() { return isVisible; }

    std::string modelName;
    std::string mainMaterialOverride;
    bool isVisible = true;

private:
    Mesh* mesh = nullptr;
    MaterialOverride materialOverride;
};