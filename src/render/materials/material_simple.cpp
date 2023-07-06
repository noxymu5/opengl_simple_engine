#include "render/materials/material_simple.h"

void MaterialSimple::SetUniforms(RenderContext ctx) {
    Material::SetUniforms(ctx);

    shader->SetUniform("ulightColor", ctx.lightsData[0]->color);
    shader->SetUniform("ulightPos", ctx.lightsData[0]->position);
    shader->SetUniform("uViewPos", ctx.viewPos);
}