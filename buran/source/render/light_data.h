#ifndef LIGHT_DATA_H
#define LIGHT_DATA_H

#include <vector>

#include <glm/vec3.hpp>

#include "scene/light.h"
#include "render/shader.h"

struct LightData {
    glm::vec3 color;
};

struct DirectionalLightData : public LightData {
    glm::vec3 direction;
};

struct PointLightData : public LightData {
    glm::vec3 position;
    float distance;
};

struct SpotLightData : public LightData {
    glm::vec3 position;
    glm::vec3 direction;
    float cutoffAngle;
    float radius;
};

struct SceneLightsData {
    DirectionalLightData* directionalLight = nullptr;
    std::vector<PointLightData*> pointLights;
    std::vector<SpotLightData*> spotLights;

    void ApplyToShader(Shader* shader) {
        
    }
};



#endif