#include "material_instance.h"

#include "resource_system/resource_system.h"
#include "resource_system/resource/resource_texture.h"

MaterialInstance::MaterialInstance(ResourceMaterial* res, Material* mat) : material(mat) {
    if (!res->textureName.empty()) {
        ResourceTexture* resTex = ResourceSystem::Get()->GetResource<ResourceTexture>(res->textureName);
        texture = new Texture(resTex->width, resTex->height, resTex->data, 0);
    }

    isLit = res->isLit;
}

void MaterialInstance::Activate(RenderContext ctx) {
    if (texture != nullptr) {
        texture->Use();
    }
    material->Activate(ctx);
    material->SetIsLit(isLit);
}

void MaterialInstance::Deactivate() {
    if (texture != nullptr) {
        texture->Deactivate();
    }
    material->Deactivate();
}