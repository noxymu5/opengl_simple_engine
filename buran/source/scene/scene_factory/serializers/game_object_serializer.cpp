#include "game_object_serializer.h"

#include <glm/vec3.hpp>

#include "dependencies_ext/yaml_cpp/converters.h"
#include "game_components/serializers/game_component_serializer.h"

const char* keyPosition = "pos";
const char* keyScale = "scale";
const char* keyRotation = "rotation";
const char* keyComponents = "components";
const char* keyIsEnabled = "isEnabled";

void GameObjectSerializer::Deserialize(SceneFactory* sceneFactory, Scene* scene, std::string name, YAML::Node gameObjectContents) {
    GameObject* gameObject = CreateGameObject(scene, name);

    ReadContents(gameObject, gameObjectContents);

    if (gameObjectContents[keyComponents]) {
        YAML::Node components = gameObjectContents[keyComponents];
            
        LOG("Start creating components")
        for(YAML::const_iterator it = components.begin(); it != components.end(); ++it) {
            std::string componentName = "GameComponent" + it->first.as<std::string>();

            GameComponentSerializer* serializer = sceneFactory->GetGameComponentSerializer(componentName);
            if (serializer == nullptr) {
                continue;
            }

            LOG("creating component %s", componentName.c_str())

            serializer->Deserialize(gameObject, it->second);
        }
        LOG("Finish creating components")
    }
    
    gameObject->Init();
}

void GameObjectSerializer::ReadContents(GameObject* gameObject, YAML::Node gameObjectContents) {
    if (gameObjectContents[keyPosition]) {
        YAML::Node position = gameObjectContents[keyPosition];
        gameObject->SetPos(position.as<glm::vec3>());
    }

    if (gameObjectContents[keyScale]) {
        YAML::Node scale = gameObjectContents[keyScale];
        if (scale.IsSequence()) {
            gameObject->SetScale(scale.as<glm::vec3>());
        } else {
            gameObject->SetScale(scale.as<float>());
        }
    }

    if (gameObjectContents[keyRotation]) {
        YAML::Node rotation = gameObjectContents[keyRotation];
        glm::vec3 angles = rotation.as<glm::vec3>();

        gameObject->GetTransform().SetEulerAngles(angles);
    }

    if (gameObjectContents[keyIsEnabled]) {
        YAML::Node isEnabledYaml = gameObjectContents[keyIsEnabled];
        bool isEnabled = isEnabledYaml.as<bool>();

        gameObject->SetEnabled(isEnabled);
    }
}

GameObject* GameObjectSerializer::CreateGameObject(Scene* scene, std::string name) {
    return scene->CreateGameObject(name);
}