#include "game_components/game_component_geometry.h"

#include <GLFW/glfw3.h>
#include "game_components/serializers/game_component_serializer.h"

#include "resource_system/resource/resource_mesh.h"
#include "resource_system/resource/resource_material.h"
#include "resource_system/resource/resource_texture.h"
#include "resource_system/resource_system.h"

BEGIN_SERIALIZER(GameComponentGeometry)
EXPOTR_FIELD(modelName, std::string)
EXPOTR_FIELD(mainMaterialOverride, std::string)
EXPOTR_FIELD(isVisible, bool)
END_SERIALIZER(GameComponentGeometry)

void GameComponentGeometry::Init() {
    materialOverride.mainMaterialName = mainMaterialOverride;

    mesh = new Mesh(modelName, materialOverride);
}

void GameComponentGeometry::Draw(RenderContext ctx) {
    mesh->Draw(ctx);
}