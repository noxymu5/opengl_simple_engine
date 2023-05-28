#ifndef SCENE_H
#define SCENE_H

#include <vector>

class GameObject;
class Camera;

class Scene {
public:
    Scene();

    void Update(float dt);

    GameObject* CreateGameObject();
    Camera* CreateCamera();
    Camera* GetCamera() { return camera; }
    std::vector<GameObject*>& GetGameObjects() { return objects; }

private:
    std::vector<GameObject*> objects;
    Camera* camera = nullptr;

    void RegisterGameObject(GameObject* gameObject);
};

#endif