#pragma once

#include "resource_system/resource/resource_material.h"
#include "render/texture/texture.h"

class MaterialInstance {
public:
    MaterialInstance(ResourceMaterial* res, Material* mat);
    void Activate(RenderContext ctx);
    void Deactivate();

private:
    Material* material = nullptr;
    Texture* texture = nullptr;
    bool isLit = true;
};