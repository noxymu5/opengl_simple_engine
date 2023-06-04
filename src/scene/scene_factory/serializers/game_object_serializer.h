#ifndef GAME_OBJECT_SERIALIZER_H
#define GAME_OBJECT_SERIALIZER_H

#include <string>

#include <yaml-cpp/yaml.h>

#include "scene/scene_factory/scene_factory.h"
#include "scene/scene.h"
#include "scene/game_object.h"

class GameObjectSerializer {
public:
    void Deserialize(SceneFactory* sceneFactory, Scene* scene, std::string name, YAML::Node gameObjectContents);
protected:
    virtual GameObject* CreateGameObject(Scene* scene, std::string name);
};

#endif