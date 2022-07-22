#include "application_cube_fall.h"

#include "helpers.h"

const float PI = glm::pi<float>();

Transform ApplicationCubeFall::CreateRandomizedTransform(bool fixedY) {

    float rndX = glm::linearRand(-PI, PI);
    float rndY = glm::linearRand(-PI * 2, PI * 2);
    float rndZ = glm::linearRand(-PI, PI);

    float rndRot = glm::linearRand(0.0, 2.0 * PI);
    float rndScale = glm::linearRand(0.2, 1.0);

    Transform res;
    res.Scale(glm::vec3(1.0) * rndScale);
    res.Translate(glm::vec3(rndX, (fixedY ? 7 : rndY), rndZ));
    res.Rotate((float)rndRot, glm::vec3(0.1, 0.5, 1));

    return res;
}

void ApplicationCubeFall::Init() {
    proj = glm::perspective(glm::radians(45.0f), windowWidth/windowHeight, 0.1f, 100.0f);

    texture = new Texture(HELPERS::AssetPath("textures/container.jpg"), GL_RGB);
    cubeShader = new Shader(HELPERS::ShaderPath("simple_lit_shader.glsl"));
    lightSourceShader = new Shader(HELPERS::ShaderPath("light_source.glsl"));
    
    vaoCube = new VertexArrayObject();
    vaoCube->Bind();
        vBufferCube = new VertexBuffer(HELPERS::cubeVertexDataUvNormals, sizeof(HELPERS::cubeVertexDataUvNormals));
        cubeShader->BindVertexAttributes();
    vaoCube->UnBind();
    
    vaoLightSource = new VertexArrayObject();
    vaoLightSource->Bind();
        vBufferLightSource = new VertexBuffer(HELPERS::cubeVertexData, sizeof(HELPERS::cubeVertexData));
        lightSourceShader->BindVertexAttributes();
    vaoLightSource->UnBind();

    for (int i = 0; i < 36; ++i) {
        cubeTransforms[i] = CreateRandomizedTransform();
    }

    lightSourceTrf.Scale(glm::vec3(0.3f));
}

void ApplicationCubeFall::UpdateScreenSize(int newWidth, int newHeight) {
    ApplicationBase::UpdateScreenSize(newWidth, newHeight);

    proj = glm::perspective(glm::radians(45.0f), windowWidth/windowHeight, 0.1f, 100.0f);
}

void ApplicationCubeFall::ExecuteLoop(float dt) {
    currentMixFactor += mixFactorSpeed * dt;
    if (currentMixFactor > 1 || currentMixFactor < 0) {
        mixFactorSpeed *= -1;
    }
    glm::mat4 viewProj = proj * camera->GetCameraMatr();

    vaoLightSource->Bind();
        lightSourceShader->Use();
        lightSourceShader->SetUniform("trf", viewProj * lightSourceTrf.Get());        
        glDrawArrays(GL_TRIANGLES, 0, 36);
    vaoLightSource->UnBind();

    vaoCube->Bind();
        cubeShader->Use();
        for(int i = 0; i < 36; ++i) {
            cubeTransforms[i].Rotate(dt, glm::vec3(0.1, 0.5, 1));
            cubeTransforms[i].Translate(glm::vec3(0, -1, 0) * dt * moveDownSpeed);

            cubeShader->SetUniform("viewProj", viewProj);
            cubeShader->SetUniform("model", cubeTransforms[i].Get());
            cubeShader->SetUniform("ulightColor", lightColor);
            cubeShader->SetUniform("ulightPos", lightSourceTrf.Get()[3]);
            cubeShader->SetUniform("uViewPos", camera->GetCameraMatr()[3]);
            
            glDrawArrays(GL_TRIANGLES, 0, 36);

            glm::vec3 currPos = cubeTransforms[i].GetPosition();
            if (currPos[1] < -7) {
                cubeTransforms[i] = CreateRandomizedTransform(true);
            }
        }
    vaoCube->UnBind();
}