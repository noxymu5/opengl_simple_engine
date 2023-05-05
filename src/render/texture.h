#ifndef TEXTURE
#define TEXTURE

#include <string>

class Texture
{
public:
    Texture();
    Texture(std::string pathToTexture, unsigned int format, unsigned int inTextureUnit = 0);
    void Bind();

private:
    unsigned int id = -1;
    unsigned int textureUnit = -1;
};

#endif