#include "texture_loader.h"

#include <sstream>
#include <fstream>
#include "stb_image.h"

#include "core/asserts.h"
#include "core/logging.h"

#include "resource_system/resource_system.h"
#include "resource_system/resource/resource_texture.h"

static std::string texturesRoot = "\\assets\\textures\\";

void TextureLoader::Load() {
    std::string textureFolderPath = resSys->GetRoot() + texturesRoot;

    LOG("Load textures from folder %s", textureFolderPath.c_str())

    std::filesystem::directory_entry entry{textureFolderPath};
    ASSERT(entry.exists(), "Directory %s does not exist", textureFolderPath.c_str())
    ASSERT(entry.is_directory(), "Path %s does not lead to directory", textureFolderPath.c_str())

    std::vector<std::filesystem::path> texturesPath;
    CollectItemsPath(texturesPath, textureFolderPath);

    for(std::filesystem::path path : texturesPath) {
        std::string pathAsString = path.string();

        ResourceTexture* resource = new ResourceTexture();
        resource->data = stbi_load(pathAsString.c_str(), &resource->width, &resource->height, &resource->nrChannels, 4);

        if (resource->data == nullptr) {
            LOG("Can not load resource by path %s. Reason: %s", path.c_str(), stbi_failure_reason())
            continue;
        }
        std::string fileName = path.filename().string();
        resSys->RegisterResource(fileName, resource);
        LOG("finished loading %s", fileName.c_str())
    }
}