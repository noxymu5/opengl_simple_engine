#include "texture.h"

#include <GLEW/glew.h>

#include "resource_system/loader/texture_loader.h"
#include "core/asserts.h"

Texture::Texture(ResourceTexture* res, unsigned int inTextureUnit) {
    Texture(res->width, res->height, res->data, inTextureUnit);
}

Texture::Texture(unsigned int width, unsigned int height, unsigned char* data, unsigned int inTextureUnit) {
    textureUnit = inTextureUnit;
    
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::BindTexture() {
    glBindTexture(GL_TEXTURE_2D, id);
}