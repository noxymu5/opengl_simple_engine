#include "scene.h"

#include "scene/game_object.h"
#include "scene/camera.h"
#include "scene/light.h"
#include "core/asserts.h"

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

Light* Scene::CreateLight(std::string name) {
    Light* light = new Light();
    light->SetName(name);
    lights.push_back(light);

    RegisterGameObject(light);

    return light;
}

void Scene::RegisterGameObject(GameObject* gameObject) {
    objects.push_back(gameObject);
}