#ifndef APPLICATION_BASE
#define APPLICATION_BASE

#include "common.h"
#include "camera.h"

class ApplicationBase
{
public:
    ApplicationBase(GLFWwindow* inWindow, float width, float height) 
        : window(inWindow), windowWidth(width), windowHeight(height) { camera = Camera::GetCamera(); }

    virtual void Init() = 0;
    virtual void ExecuteLoop(float dt) = 0;

protected:
    GLFWwindow* window;
    float windowWidth, windowHeight;

    Camera* camera;
};


#endif