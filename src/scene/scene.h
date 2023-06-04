#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

class GameObject;
class Camera;

class Scene {
public:
    Scene() {}

    void Update(float dt);

    GameObject* CreateGameObject(std::string name);
    Camera* CreateCamera(std::string name);
    Camera* GetCamera() { return camera; }
    std::vector<GameObject*>& GetGameObjects() { return objects; }

private:
    std::vector<GameObject*> objects;
    Camera* camera = nullptr;

    void RegisterGameObject(GameObject* gameObject);
};

#endif