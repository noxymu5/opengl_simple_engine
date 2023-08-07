#pragma once

#include"resource_system/resource/resource_texture.h"
#include "render/texture/texture_base.h"

class Texture : public TextureBase
{
public:
    Texture(ResourceTexture* res, unsigned int inTextureUnit = 0);
    Texture(unsigned int width, unsigned int height, unsigned char* data, unsigned int inTextureUnit = 0);
protected:
    virtual void BindTexture() override;
};