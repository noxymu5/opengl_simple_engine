#ifndef APPLICATION_CUBE_FALL
#define APPLICATION_CUBE_FALL

#include <glm/gtc/random.hpp>

#include "application_base.h"

#include "shader.h"
#include "texture.h"
#include "buffers.h"
#include "vertex_array_object.h"
#include "transform.h"

class ApplicationCubeFall : public ApplicationBase
{
public:
    ApplicationCubeFall(GLFWwindow* inWindow, float width, float height) 
        : ApplicationBase(inWindow, width, height) {}

    virtual void Init() override;
    virtual void ExecuteLoop(float dt) override;

private:
    Transform CreateRandomizedTransform(bool fixedY = false);

    glm::mat4 proj;

    VertexArrayObject* vaoCube;
    VertexBuffer* vBufferCube;

    VertexArrayObject* vaoLightSource;
    VertexBuffer* vBufferLightSource;

    Shader* cubeShader;
    Shader* lightSourceShader;
    Texture* texture;

    float mixFactorSpeed = 1;
    float currentMixFactor = 0;
    float moveDownSpeed = 1;

    Transform cubeTransforms[36];

    Transform lightSourceTrf;

    glm::vec3 lightColor = glm::vec3(1.0f);
};


#endif