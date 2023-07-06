#ifndef TEXTURE
#define TEXTURE

#include "resource_system/resource/resource_texture.h"

class Texture
{
public:
    Texture(ResourceTexture* res, unsigned int inTextureUnit = 0);
    void Use();
    void Deactivate();

private:
    unsigned int id = -1;
    unsigned int textureUnit = -1;
};

#endif