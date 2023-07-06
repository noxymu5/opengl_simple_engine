#include "material.h"

#include "resource_system/resource/resource_shader.h"

void Material::LoadShader(ResourceSystem* resSys) {
    ResourceShader* resourceShader = resSys->GetResource<ResourceShader>(GetShaderName());
    shader = new Shader(resourceShader);
}

void Material::Activate(RenderContext ctx) {
    shader->Use();
    shader->BindVertexAttributes();
    SetUniforms(ctx);
}

void Material::Deactivate() {

}

void Material::SetUniforms(RenderContext ctx) {
    shader->SetUniform("viewProj", ctx.viewProj);
    shader->SetUniform("model", ctx.model);
}