#include "game_object_serializer.h"

#include <glm/vec3.hpp>

#include "dependencies_ext/yaml_cpp/converters.h"
#include "game_components/serializers/game_component_serializer.h"

const char* keyPosition = "pos";
const char* keyScale = "scale";
const char* keyComponents = "components";

void GameObjectSerializer::Deserialize(SceneFactory* sceneFactory, Scene* scene, std::string name, YAML::Node gameObjectContents) {
    GameObject* gameObject = CreateGameObject(scene, name);

    if (gameObjectContents[keyPosition]) {
        YAML::Node position = gameObjectContents[keyPosition];
        gameObject->SetPos(position.as<glm::vec3>());
    }

    if (gameObjectContents[keyScale]) {
        YAML::Node scale = gameObjectContents[keyScale];
        gameObject->SetScale(scale.as<glm::vec3>());
    }

    YAML::Node components = gameObjectContents[keyComponents];
    
    LOG("Start creating components")
    for(YAML::const_iterator it = components.begin(); it != components.end(); ++it) {
        auto first = it->first;

        GameComponentSerializer* serializer = sceneFactory->GetGameComponentSerializer(first.as<std::string>());
        if (serializer == nullptr) {
            continue;
        }

        serializer->Deserialize(gameObject, it->second);
    }
    LOG("Finish creating components")
    
    gameObject->Init();
}

GameObject* GameObjectSerializer::CreateGameObject(Scene* scene, std::string name) {
    return scene->CreateGameObject(name);
}