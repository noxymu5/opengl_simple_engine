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

    shader = new Shader("../shaders/simple_vertex_shader.vs", "../shaders/simple_fragment_shader.fs", 5 * sizeof(float));

    texture0 = new Texture("../assets/textures/container.jpg", GL_RGB);
    texture1 = new Texture("../assets/textures/kotik_yuy.jpg", GL_RGB, 1);
    
    vao = new VertexArrayObject();
    vao->Bind();
        vBuffer = new VertexBuffer(cubeVertexData, sizeof(cubeVertexData));

        shader->SetVertexAttribute("aPos", 3, GL_FLOAT, GL_FALSE, 0);
        shader->SetVertexAttribute("aTexCoords", 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
    vao->UnBind();

    shader->Use();
    shader->SetUniform("texture0", 0);
    shader->SetUniform("texture1", 1);

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
    shader->SetUniform("mixFactor", currentMixFactor);

    texture0->Bind();
    texture1->Bind();

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