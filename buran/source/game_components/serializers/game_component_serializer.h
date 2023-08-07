#pragma once

#include <yaml-cpp/yaml.h>

#include "scene/game_object.h"
#include "scene/scene_factory/scene_factory.h"
#include "game_components/serializers/game_component_serializer.h"

class GameComponentSerializer {
public:
    virtual void Deserialize(GameObject* gameObject, YAML::Node contents) {};
};

#define BEGIN_SERIALIZER(CompName) \
    class CompName##Serializer : public GameComponentSerializer { \
    public: \
        virtual void Deserialize(GameObject* gameObject, YAML::Node contents) override; \
    }; \
    void CompName##Serializer::Deserialize(GameObject* gameObject, YAML::Node contents) { \
        CompName* comp = gameObject->AddComponent<CompName>(); \
        if (contents.IsNull()) { \
            return; \
        } \

#define EXPOTR_FIELD(fieldName, type) \
        if (contents[#fieldName]) { \
            comp->fieldName = contents[#fieldName].as<type>(); \
        } \

#define END_SERIALIZER(CompName) \
    } \
    void CompName##RegisterSerializer(SceneFactory* factory) { factory->RegisterComponentSerializer(#CompName, new CompName##Serializer()); };

#define REGISTER_COMPONENT(CompName, sceneFactory) \
    { \
        extern void CompName##RegisterSerializer(SceneFactory* factory); \
        CompName##RegisterSerializer(sceneFactory); \
    }