#include "texture_base.h"

#include <GLEW/glew.h>

#include "resource_system/loader/texture_loader.h"
#include "core/asserts.h"

TextureBase::~TextureBase() {
    glDeleteTextures(1, &id);
}

void TextureBase::Use() {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    BindTexture();
}

void TextureBase::Deactivate() {
    glBindTexture(GL_TEXTURE_2D, 0);
}