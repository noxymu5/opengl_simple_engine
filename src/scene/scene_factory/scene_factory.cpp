#include "scene_factory.h"

#include <string>
#include <map>

#include <yaml-cpp/yaml.h>

#include "core/logging.h"
#include "core/asserts.h"

#include "serializers/game_object_serializer.h"
#include "serializers/camera_serializer.h"

struct GameObjectCreationData {
    std::string name;
    YAML::Node contents;
    Scene* scene;
};

std::map<std::string, GameObjectSerializer*> serializerStorage = {
    {"GameObject", new GameObjectSerializer()},
    {"Camera", new CameraSerializer()}
};

const std::string keyGameObjects = "objects";

Scene* SceneFactory::CreateScene(ApplicationArguments arguments) {
    Scene* scn = new Scene();

    std::string scenePath = arguments.TryGetArgument(ArgumentType::SCENE_NAME);
    YAML::Node yamlScene = YAML::LoadFile(scenePath.c_str());
    
    YAML::Node gameObjets = yamlScene[keyGameObjects];
    ASSERT(!gameObjets.IsNull(), "Scene file %s does not contain objects section", scenePath.c_str())
    
    LOG("Started loading scene by path %s", scenePath.c_str())
    for(YAML::const_iterator it = gameObjets.begin(); it != gameObjets.end(); ++it) {
        auto first = it->first;
        auto second = it->second;
        
        std::string name = first.as<std::string>();
        ASSERT(second.IsMap(), "section %s should be a yaml map to be processed", name.c_str())

        CreateGameObject({name, second, scn});
    }

    if (scenePath.empty()) {
        LOG("No scene path provided, creating empty scene")
        scn->CreateCamera("MainCamera");
    }

    return scn;
}

void SceneFactory::CreateGameObject(GameObjectCreationData data) {
    std::string type = data.contents["type"].as<std::string>();

    LOG("Creating game object %s of type %s", data.name.c_str(), type.c_str())

    auto serializerIt = serializerStorage.find(type);

    if (serializerIt == serializerStorage.end()) {
        LOG("Can not find serializer for type %s", type.c_str())
        return;
    }

    serializerIt->second->Deserialize(this, data.scene, data.name, data.contents);
}

void SceneFactory::RegisterComponentSerializer(std::string typeAsString, GameComponentSerializer* serializer) {
    gameComponentSerializers[typeAsString] = serializer;
}

GameComponentSerializer* SceneFactory::GetGameComponentSerializer(std::string componentType) {
    auto serializerIt = gameComponentSerializers.find(componentType);
    if (serializerIt == gameComponentSerializers.end()) {
        LOG("unknown game component %s", componentType.c_str())
        return nullptr;
    }

    return serializerIt->second;
}