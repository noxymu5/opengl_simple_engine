#pragma once

#include "game_object_serializer.h"

class CameraSerializer : public GameObjectSerializer {
protected:
    virtual GameObject* CreateGameObject(Scene* scene, std::string name) override;
};