#ifndef TEXTURE
#define TEXTURE

#include "resource_system/resource/resource_texture.h"

class Texture
{
public:
    Texture(ResourceTexture* res, unsigned int inTextureUnit = 0);
    Texture(unsigned int width, unsigned int height, unsigned char* data, unsigned int inTextureUnit = 0);

    ~Texture();

    void Use();
    void Deactivate();
    unsigned int Id() { return id; }

private:
    unsigned int id = 0;
    unsigned int textureUnit = 0;
};

#endif