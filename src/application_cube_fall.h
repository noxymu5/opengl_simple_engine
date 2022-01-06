#ifndef APPLICATION_CUBE_FALL
#define APPLICATION_CUBE_FALL

#include <glm/gtc/random.hpp>

#include "application_base.h"

#include "helpers.h"

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

    VertexArrayObject* vao;
    VertexBuffer* vBuffer;

    Shader* shader;
    Texture* texture0;
    Texture* texture1;

    float mixFactorSpeed = 1;
    float currentMixFactor = 0;
    float moveDownSpeed = 1;

    Transform cubeTransforms[36];
};


#endif