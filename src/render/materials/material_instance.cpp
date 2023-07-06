#include "material_instance.h"

#include "resource_system/resource_system.h"
#include "resource_system/resource/resource_texture.h"

MaterialInstance::MaterialInstance(ResourceMaterial* res, Material* mat) : material(mat) {
    texture = new Texture(ResourceSystem::Get()->GetResource<ResourceTexture>(res->textureName), 0);
}

void MaterialInstance::Activate(RenderContext ctx) {
    texture->Use();
    material->Activate(ctx);
}

void MaterialInstance::Deactivate() {
    texture->Deactivate();
    material->Deactivate();
}