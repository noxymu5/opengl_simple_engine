#pragma once

#include <string>

#include <yaml-cpp/yaml.h>

#include "scene/scene_factory/scene_factory.h"
#include "scene/scene.h"
#include "scene/game_object.h"

class GameObjectSerializer {
public:
    void Deserialize(SceneFactory* sceneFactory, Scene* scene, std::string name, YAML::Node gameObjectContents);
protected:
    virtual void ReadContents(GameObject* gameObject, YAML::Node gameObjectContents);
    virtual GameObject* CreateGameObject(Scene* scene, std::string name);
};