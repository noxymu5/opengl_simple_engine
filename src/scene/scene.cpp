#include "scene.h"

#include "scene/game_object.h"
#include "scene/camera.h"
#include "core/asserts.h"
#include "scene/game_component_fly_camera.h"

Scene::Scene() {
    Camera* cam = CreateCamera();
    cam->SetPos(glm::vec3(0.0, 0.0, 3.0));

    cam->AddComponent<GameComponentFlyCamera>();
}

void Scene::Update(float dt) {
    for(int i = 0; i < objects.size(); ++i) {
        objects[i]->Update(dt);
    }
}

GameObject* Scene::CreateGameObject() {
    GameObject* object = new GameObject();
    RegisterGameObject(object);

    return object;
}

Camera* Scene::CreateCamera() {
    camera = new Camera();
    RegisterGameObject(camera);

    return camera;
}

void Scene::RegisterGameObject(GameObject* gameObject) {
    objects.push_back(gameObject);
}