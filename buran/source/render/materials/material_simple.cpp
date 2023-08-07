#include "render/materials/material_simple.h"

#include "render/light_data.h"
#include "core/logging.h"

void MaterialSimple::SetUniforms(RenderContext ctx) {
    Material::SetUniforms(ctx);

    SceneLightsData* sceneLightsData = ctx.lightData;

    if (sceneLightsData->directionalLight != nullptr) {
        shader->SetUniform("uDirLight.diffuse", sceneLightsData->directionalLight->color);
        shader->SetUniform("uDirLight.direction", sceneLightsData->directionalLight->direction);
    }

    std::string prefix = "uPointLights[";
    shader->SetUniform("uPointLightsCount", (int)sceneLightsData->pointLights.size());

    for(int idx = 0; idx < sceneLightsData->pointLights.size(); ++idx) {
        std::string idxAsString = std::to_string(idx);
        std::string uniformDiffuse = prefix + idxAsString + "].diffuse";
        std::string uniformPosition = prefix + idxAsString + "].position";
        std::string uniformRadius = prefix + idxAsString + "].radius";

        shader->SetUniform(uniformDiffuse.c_str(), sceneLightsData->pointLights[idx]->color);
        shader->SetUniform(uniformPosition.c_str(), sceneLightsData->pointLights[idx]->position);
        shader->SetUniform(uniformRadius.c_str(), sceneLightsData->pointLights[idx]->distance);
    }

    prefix = "uSpotLights[";
    shader->SetUniform("uSpotLightsCount", (int)sceneLightsData->spotLights.size());

    for(int idx = 0; idx < sceneLightsData->spotLights.size(); ++idx) {
        std::string idxAsString = std::to_string(idx);
        std::string uniformDiffuse = prefix + idxAsString + "].diffuse";
        std::string uniformPosition = prefix + idxAsString + "].position";
        std::string uniformCutoff = prefix + idxAsString + "].cutoffAngle";
        std::string uniformDirection = prefix + idxAsString + "].direction";
        std::string uniformRadius = prefix + idxAsString + "].radius";

        shader->SetUniform(uniformDiffuse.c_str(), sceneLightsData->spotLights[idx]->color);
        shader->SetUniform(uniformPosition.c_str(), sceneLightsData->spotLights[idx]->position);
        shader->SetUniform(uniformCutoff.c_str(), sceneLightsData->spotLights[idx]->cutoffAngle);
        shader->SetUniform(uniformDirection.c_str(), sceneLightsData->spotLights[idx]->direction);
        shader->SetUniform(uniformRadius.c_str(), sceneLightsData->spotLights[idx]->radius);
    }

    shader->SetUniform("uViewPos", ctx.viewPos);
}