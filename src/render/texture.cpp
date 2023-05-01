#include "texture.h"

#include "stb_image.h"

Texture::Texture(std::string pathToTexture, GLenum format, unsigned int inTextureUnit) : textureUnit(inTextureUnit) {
    int width, height, nrChannels;
    unsigned char *textureData = stbi_load(pathToTexture.c_str(), &width, &height, &nrChannels, 0);
    if (!textureData) {
        std::cout << "ERROR::TEXTURE::LOAD_FAILED" << std::endl;
        return;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureData);
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, id);
}