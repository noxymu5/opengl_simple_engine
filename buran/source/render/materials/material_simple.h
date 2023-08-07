#pragma once

#include "render/materials/material.h"

class MaterialSimple : public Material {
protected:
    virtual void SetUniforms(RenderContext ctx) override;

private:
    virtual std::string GetShaderName() override { return "simple_lit_shader.glsl"; } 

};