#ifndef LIGHT_SERIALIZER_H
#define LIGHT_SERIALIZER_H

#include "game_object_serializer.h"

class LightSerializer : public GameObjectSerializer {
protected:
    virtual GameObject* CreateGameObject(Scene* scene, std::string name) override;
    virtual void ReadContents(GameObject* gameObject, YAML::Node gameObjectContents) override;
};

#endif