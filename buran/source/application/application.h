#ifndef APPLICATION_H
#define APPLICATION_H

struct GLFWwindow;

class ApplicationArguments;

class ResourceSystem;
class InputSystem;
class Renderer;
class MaterialSystem;
class Scene;
class SceneFactory;

class Application {
public:
    Application();

    void Init(ApplicationArguments args);
    void Terminate();
    void Execute();
    
    void Resize(GLFWwindow* window, int windowWidth, int windowHeight);

private:
    SceneFactory* sceneFactory = nullptr;

    ResourceSystem* resSystem = nullptr;
    InputSystem* inputSystem = nullptr;
    Renderer* renderer = nullptr;
    MaterialSystem* matSystem = nullptr;
    Scene* currentScene = nullptr;

    GLFWwindow* window = nullptr;

    int windowWidth = 1280;
    int windowHeight = 720;

    void CreateWindow();
    bool IsWindowOpen() const;
    static void GlErrorCallback(int error, const char* description);
    void RegisterComponents(SceneFactory* SceneFactory);
    
};

#endif