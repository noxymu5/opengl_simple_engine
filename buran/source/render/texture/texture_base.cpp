#include "texture_base.h"

#include <glbinding/gl/gl.h>

#include "resource_system/loader/texture_loader.h"
#include "core/asserts.h"

TextureBase::~TextureBase() {
    gl::glDeleteTextures(1, &id);
}

void TextureBase::Use() {
    gl::glActiveTexture(gl::GL_TEXTURE0 + textureUnit);
    BindTexture();
}

void TextureBase::Deactivate() {
    gl::glBindTexture(gl::GL_TEXTURE_2D, 0);
}