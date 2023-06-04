#include "application/application.h"

#include "scene/scene_factory/scene_factory.h"
#include "game_components/serializers/game_component_serializer.h"

void Application::RegisterComponents(SceneFactory* sceneFactory) {
    REGISTER_COMPONENT(GameComponentGeometry, sceneFactory)
    REGISTER_COMPONENT(GameComponentFlyCamera, sceneFactory)
}