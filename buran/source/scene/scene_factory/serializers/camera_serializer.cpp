#include "camera_serializer.h"

GameObject* CameraSerializer::CreateGameObject(Scene* scene, std::string name) {
    return (GameObject*)(scene->CreateCamera(name));
}