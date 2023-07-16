#ifndef MATERIAL_H
#define MATERIAL_H

#include "resource_system/resource_system.h"
#include "render/shader.h"

#include "render/render_context.h"

enum class MaterialType {
    SIMPLE
};

class Material {
public:
    void LoadShader(ResourceSystem* resSys);
    virtual void Activate(RenderContext ctx);
    virtual void Deactivate();
    void SetIsLit(bool isLit) { shader->SetUniform("uIsLit", isLit); }

protected:
    Shader* shader;
    virtual void SetUniforms(RenderContext ctx);

private:
    virtual std::string GetShaderName() = 0;
};

#endif