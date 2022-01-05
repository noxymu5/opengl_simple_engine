#ifndef TEXTURE
#define TEXTURE

#include <string>
#include <iostream>

#include <GLEW/glew.h>
#include "stb_image.h"

class Texture
{
public:
    Texture(std::string pathToTexture, GLenum format, unsigned int inTextureUnit = 0);
    void Bind();

private:
    unsigned int id = -1;
    unsigned int textureUnit = -1;
};

#endif