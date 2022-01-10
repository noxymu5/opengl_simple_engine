#include "application_cube_fall.h"

Transform ApplicationCubeFall::CreateRandomizedTransform(bool fixedY) {

    float rndX = glm::linearRand(-M_PI, M_PI);
    float rndY = glm::linearRand(-M_PI * 2, M_PI * 2);
    float rndZ = glm::linearRand(-M_PI, M_PI);

    float rndRot = glm::linearRand(0.0, 2.0 * M_PI);
    float rndScale = glm::linearRand(0.0, M_PI) / M_PI;

    Transform res;
    res.Scale(glm::vec3(1.0) * rndScale);
    res.Translate(glm::vec3(rndX, (fixedY ? 5 : rndY), rndZ));
    res.Rotate((float)rndRot, glm::vec3(0.1, 0.5, 1));

    return res;
}

void ApplicationCubeFall::Init() {
    proj = glm::perspective(glm::radians(45.0f), windowWidth/windowHeight, 0.1f, 100.0f);

    texture = new Texture("../assets/textures/container.jpg", GL_RGB);
    shader = new Shader("../shaders/simple_shader.glsl");
    
    vao = new VertexArrayObject();
    vao->Bind();
        vBuffer = new VertexBuffer(HELPERS::cubeVertexData, sizeof(HELPERS::cubeVertexData));
        shader->BindVertexAttributes();
    vao->UnBind();

    for (int i = 0; i < 36; ++i) {
        cubeTransforms[i] = CreateRandomizedTransform();
    }
}

void ApplicationCubeFall::ExecuteLoop(float dt) {
    currentMixFactor += mixFactorSpeed * dt;
    if (currentMixFactor > 1 || currentMixFactor < 0) {
        mixFactorSpeed *= -1;
    }

    shader->Use();
    vao->Bind();
        for (int i = 0; i < 36; ++i) {
            cubeTransforms[i].Rotate(dt, glm::vec3(0.1, 0.5, 1));
            cubeTransforms[i].Translate(glm::vec3(0, -1, 0) * dt * moveDownSpeed);

            glm::mat4 mvpMatr = proj * camera->GetCameraMatr() * cubeTransforms[i].Get();
            shader->SetUniform("trf", &mvpMatr);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            glm::vec3 currPos = cubeTransforms[i].GetPosition();
            if (currPos[1] < -5) {
                cubeTransforms[i] = CreateRandomizedTransform(true);
            }
        }
    vao->UnBind();
}