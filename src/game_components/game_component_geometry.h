#ifndef GAME_COMPONENT_GEOMETRY_H
#define GAME_COMPONENT_GEOMETRY_H

#include <string>

#include "resource_system/resource/resource_mesh.h"

#include "game_components/game_component.h"
#include "render/buffers.h"
#include "render/vertex_array_object.h"
#include "render/texture.h"

class GameComponentGeometry : public GameComponent {
public:
    INIT_COMPONENT(GameComponentGeometry)

    GameComponentGeometry(GameObject* owner) : GameComponent(owner) {}

    virtual void Init() override;

    void StartDraw();
    void EndDraw();

    void SetVisible(bool val) { isVisible = val; }
    bool IsVisible() { return isVisible; }

    std::string modelName;
private:

    bool isVisible = true;

    ResourceMesh* mesh;

    Texture* texture = nullptr;
    VertexArrayObject* vao;
    VertexBuffer* vertexBuffer;
    IndexBuffer* indexBuffer;
};

#endif