#include "texture.h"

#include <GLEW/glew.h>

#include "resource_system/loader/texture_loader.h"
#include "core/asserts.h"

Texture::Texture(ResourceTexture* res, unsigned int inTextureUnit) : textureUnit(inTextureUnit) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, res->width, res->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, res->data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::Use() {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Deactivate() {
    glBindTexture(GL_TEXTURE_2D, 0);
}