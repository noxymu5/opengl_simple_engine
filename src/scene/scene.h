#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>

class GameObject;
class Camera;
class Light;

class Scene {
public:
    Scene() {}

    void Update(float dt);

    GameObject* CreateGameObject(std::string name);
    Camera* CreateCamera(std::string name);
    Light* CreateLight(std::string name);
    Camera* GetCamera() { return camera; }
    
    std::vector<Light*> GetLights();
    std::vector<GameObject*>& GetGameObjects() { return objects; }

private:
    std::vector<GameObject*> objects;
    std::vector<Light*> lights;
    Camera* camera = nullptr;

    void RegisterGameObject(GameObject* gameObject);
};

#endif