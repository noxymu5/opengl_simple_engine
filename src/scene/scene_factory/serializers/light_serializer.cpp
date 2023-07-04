#include "light_serializer.h"

#include <glm/vec3.hpp>

#include "dependencies_ext/yaml_cpp/converters.h"

#include "scene/light.h"

const char* keyType = "light_type";
const char* keyColor = "color";
const char* keyDistance = "distance";

void LightSerializer::ReadContents(GameObject* gameObject, YAML::Node gameObjectContents){
    GameObjectSerializer::ReadContents(gameObject, gameObjectContents);
    
    Light* light = (Light*)gameObject;

    if (gameObjectContents[keyType]) {
        YAML::Node type = gameObjectContents[keyType];
        
        light->type = type.as<LIGHT_TYPE>();
    }

    if (gameObjectContents[keyColor]) {
        YAML::Node color = gameObjectContents[keyColor];
        light->color = color.as<glm::vec3>();
    }

    if (gameObjectContents[keyDistance]) {
        YAML::Node distance = gameObjectContents[keyDistance];
        light->distance = distance.as<float>();
    }
}

GameObject* LightSerializer::CreateGameObject(Scene* scene, std::string name) {
    return (GameObject*)(scene->CreateLight(name));
}