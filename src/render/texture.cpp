#include "texture.h"

#include <GLEW/glew.h>

#include "resource_system/texture_loader.h"
#include "core/asserts.h"

Texture::Texture(std::string pathToTexture, unsigned int format, unsigned int inTextureUnit) : textureUnit(inTextureUnit) {
    TextureLoader loader(pathToTexture);
    
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, loader.Width(), loader.Height(), 0, format, GL_UNSIGNED_BYTE, loader.Get());
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, id);
}