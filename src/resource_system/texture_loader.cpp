#include "texture_loader.h"

#include <sstream>
#include <fstream>
#include "stb_image.h"

#include "resource_system/resource_system.h"
#include "core/asserts.h"

TextureLoader::TextureLoader(std::string path) {
    ResourceSystem* resSystem = ResourceSystem::Get();
    std::string resultPath = resSystem->PathToTexture(path);

    data = stbi_load(resultPath.c_str(), &width, &height, &nrChannels, 0);
    ASSERT(data != nullptr, "Can not load texture by path %s. Reason: %s", resultPath.c_str(), stbi_failure_reason())
}

TextureLoader::~TextureLoader() {
    stbi_image_free(data);    
}