#include "texture_skybox.h"

#include <GLEW/glew.h>

#include "resource_system/resource_system.h"
#include "resource_system/resource/resource_texture.h"

#include <map>

/*
Face textures layout inside skybox texture.
-----------------
| 0 |~1~| 2 | 3 |
-----------------
|~4~|~5~|~6~|~7~|
-----------------
| 8 |~9~| 10| 11|
-----------------
*/ 

static int targetToDataId[] = {
    6, // right
    4, // left
    1, // top
    9, // bottom
    5, // front
    7  // back
};

static const int textureChannelCount = 4;
static const int texturesCountByWidth = 4;

TextureSkybox::TextureSkybox(std::string textureName) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    ResourceSystem* resSys = ResourceSystem::Get();
    ResourceTexture* res = resSys->GetResource<ResourceTexture>(textureName);

    int sideSize = res->width / texturesCountByWidth;
    int bufferSize = sideSize * sideSize * textureChannelCount;

    std::map<int, char*> idToTextureData;
    idToTextureData[1] = new char[bufferSize];
    idToTextureData[4] = new char[bufferSize];
    idToTextureData[5] = new char[bufferSize];
    idToTextureData[6] = new char[bufferSize];
    idToTextureData[7] = new char[bufferSize];
    idToTextureData[9] = new char[bufferSize];

    for (int y = 0; y < res->height; ++y) {
        for (int x = 0; x < res->width; ++x) {
            int id = (y / sideSize) * texturesCountByWidth + x / sideSize;

            auto iter = idToTextureData.find(id);
            if (iter == idToTextureData.end()) {
                continue;
            }
            
            for (int channelIdx = 0; channelIdx < textureChannelCount; ++channelIdx) {
                int sourcePixelChannelIdx = y * res->width * textureChannelCount + (x * textureChannelCount + channelIdx);
                int targetPixelChannelIdx = (y % sideSize) * sideSize * textureChannelCount + ((x % sideSize) * textureChannelCount + channelIdx);

                iter->second[targetPixelChannelIdx] = res->data[sourcePixelChannelIdx];
            }
        }
    }

    for (int target = 0; target < 6; ++target) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + target, 0, GL_RGBA, 
            sideSize, sideSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, idToTextureData[targetToDataId[target]]);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureSkybox::BindTexture() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}