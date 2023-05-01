#ifndef TEXTURE
#define TEXTURE

#include "core/common.h"

class Texture
{
public:
    Texture();
    Texture(std::string pathToTexture, GLenum format, unsigned int inTextureUnit = 0);
    void Bind();

private:
    unsigned int id = -1;
    unsigned int textureUnit = -1;
};

#endif