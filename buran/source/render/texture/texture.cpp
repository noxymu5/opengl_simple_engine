#include "texture.h"

#include <glbinding/gl/gl.h>

#include "resource_system/loader/texture_loader.h"
#include "core/asserts.h"

Texture::Texture(ResourceTexture* res, unsigned int inTextureUnit) {
    Texture(res->width, res->height, res->data, inTextureUnit);
}

Texture::Texture(unsigned int width, unsigned int height, unsigned char* data, unsigned int inTextureUnit) {
    textureUnit = inTextureUnit;
    
    gl::glGenTextures(1, &id);
    gl::glBindTexture(gl::GL_TEXTURE_2D, id);

    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_WRAP_S, gl::GL_REPEAT);
    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_WRAP_T, gl::GL_REPEAT);
    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MIN_FILTER, gl::GL_LINEAR_MIPMAP_LINEAR);
    gl::glTexParameteri(gl::GL_TEXTURE_2D, gl::GL_TEXTURE_MAG_FILTER, gl::GL_LINEAR);

    gl::glTexImage2D(gl::GL_TEXTURE_2D, 0, gl::GL_RGBA, width, height, 0, gl::GL_RGBA, gl::GL_UNSIGNED_BYTE, data);
    gl::glGenerateMipmap(gl::GL_TEXTURE_2D);

    gl::glBindTexture(gl::GL_TEXTURE_2D, 0);
}

void Texture::BindTexture() {
    gl::glBindTexture(gl::GL_TEXTURE_2D, id);
}