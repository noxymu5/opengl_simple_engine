#pragma once

#include <map>

#include "application/application_arguments.h"
#include "scene/scene.h"

struct GameObjectCreationData;
class GameComponentSerializer;

class SceneFactory {
public:
    Scene* CreateScene(ApplicationArguments argumets);
    void RegisterComponentSerializer(std::string typeAsString, GameComponentSerializer* serializer);
    GameComponentSerializer* GetGameComponentSerializer(std::string componentType);
protected:
    std::map<std::string, GameComponentSerializer*> gameComponentSerializers;
    void CreateGameObject(GameObjectCreationData data);
};