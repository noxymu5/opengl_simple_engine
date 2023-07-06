#ifndef APPLICATION_H
#define APPLICATION_H

class GLFWwindow;

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
    SceneFactory* sceneFactory;

    ResourceSystem* resSystem;
    InputSystem* inputSystem;
    Renderer* renderer;
    MaterialSystem* matSystem;
    Scene* currentScene;

    GLFWwindow* window;

    float windowWidth = 1280;
    float windowHeight = 720;

    void CreateWindow();
    bool IsWindowOpen() const;
    static void GlErrorCallback(int error, const char* description);
    void RegisterComponents(SceneFactory* SceneFactory);
    
};

#endif