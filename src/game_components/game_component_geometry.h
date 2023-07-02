#ifndef GAME_COMPONENT_GEOMETRY_H
#define GAME_COMPONENT_GEOMETRY_H

#include <string>

#include "resource_system/resource/resource_mesh.h"

#include "game_components/game_component.h"
#include "render/mesh/mesh.h"
#include "render/render_context.h"
#include "render/shader.h"

class GameComponentGeometry : public GameComponent {
public:
    INIT_COMPONENT(GameComponentGeometry)

    GameComponentGeometry(GameObject* owner) : GameComponent(owner) {}

    virtual void Init() override;

    void Draw(Shader* shader, RenderContext ctx);

    void SetVisible(bool val) { isVisible = val; }
    bool IsVisible() { return isVisible; }

    std::string modelName;
    bool isVisible = true;

private:
    Mesh* mesh;
};

#endif