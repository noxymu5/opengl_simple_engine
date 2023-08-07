#pragma once

#include "resource_system/resource/resource_texture.h"

class TextureBase
{
public:
    ~TextureBase();

    void Use();
    void Deactivate();
    unsigned int Id() { return id; }

protected:
    unsigned int id = 0;
    unsigned int textureUnit = 0;

    virtual void BindTexture() = 0;
};