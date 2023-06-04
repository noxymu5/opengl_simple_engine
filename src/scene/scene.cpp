#include "scene.h"

#include "scene/game_object.h"
#include "scene/camera.h"
#include "core/asserts.h"
#include "game_components/game_component_fly_camera.h"
#include "game_components/game_component_geometry.h"
#include "game_components/game_component_change_visibility.h"

void Scene::Update(float dt) {
    for(int i = 0; i < objects.size(); ++i) {
        objects[i]->Update(dt);
    }
}

GameObject* Scene::CreateGameObject(std::string name) {
    GameObject* object = new GameObject();
    object->SetName(name);
    RegisterGameObject(object);

    return object;
}

Camera* Scene::CreateCamera(std::string name) {
    camera = new Camera();
    camera->SetName(name);
    RegisterGameObject(camera);

    return camera;
}

void Scene::RegisterGameObject(GameObject* gameObject) {
    objects.push_back(gameObject);
}