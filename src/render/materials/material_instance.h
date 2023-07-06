#ifndef MATERIAL_INSTANCE_H
#define MATERIAL_INSTANCE_H

#include "resource_system/resource/resource_material.h"
#include "render/texture.h"

class MaterialInstance {
public:
    MaterialInstance(ResourceMaterial* res, Material* mat);
    void Activate(RenderContext ctx);
    void Deactivate();

private:
    Material* material;
    Texture* texture;
};

#endif