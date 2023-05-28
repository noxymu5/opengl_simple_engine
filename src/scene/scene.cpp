#include "scene.h"

#include "scene/game_object.h"
#include "scene/camera.h"
#include "core/asserts.h"
#include "game_components/game_component_fly_camera.h"
#include "game_components/game_component_geometry.h"
#include "game_components/game_component_change_visibility.h"

Scene::Scene() {
    Camera* cam = CreateCamera();
    cam->SetPos(glm::vec3(0.0, 0.0, 3.0));

    cam->AddComponent<GameComponentFlyCamera>();
    cam->Init();

    {
        GameObject* monkey = CreateGameObject();
        monkey->SetPos(glm::vec3(0.0, 0.0, -3.0));
        monkey->AddComponent<GameComponentChangeVisibility>();
        GameComponentGeometry* geom = monkey->AddComponent<GameComponentGeometry>();
        geom->modelName = "monke.fbx";
        monkey->Init();
    }

    {
        GameObject* cube = CreateGameObject();
        cube->SetPos(glm::vec3(3.0, 0.0, -3.0));
        GameComponentGeometry* geom = cube->AddComponent<GameComponentGeometry>();
        geom->modelName = "cube.fbx";
        cube->Init();
    }

    {
        GameObject* sphere = CreateGameObject();
        sphere->SetPos(glm::vec3(6.0, 0.0, -3.0));
        GameComponentGeometry* geom = sphere->AddComponent<GameComponentGeometry>();
        geom->modelName = "earth.fbx";
        sphere->Init();
    }
    
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