#include "texture.h"

Texture::Texture(std::string pathToTexture, GLenum format, unsigned int inTextureUnit) : textureUnit(inTextureUnit) {
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char *textureData = stbi_load(pathToTexture.c_str(), &width, &height, &nrChannels, 0);
    if (!textureData) {
        std::cout << "ERROR::TEXTURE::LOAD_FAILED" << std::endl;
        return;
    }

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, textureData);

    stbi_image_free(textureData);
}

void Texture::Bind() {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, id);
}