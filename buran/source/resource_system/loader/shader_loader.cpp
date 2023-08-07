#include "shader_loader.h"

#include <fstream>

#include "resource_system/resource_system.h"
#include "core/asserts.h"

static std::string shaderRoot = "\\shaders\\";

static std::vector<std::string> attributes {
    "vec2",
    "vec3"
};

void ShaderLoader::Load() {
    std::string shadersFolderPath = resSys->GetRoot() + shaderRoot;

    LOG("Load shaders from folder %s", shadersFolderPath.c_str())

    std::filesystem::directory_entry entry{shadersFolderPath};
    ASSERT(entry.exists(), "Directory %s does not exist", shadersFolderPath.c_str())
    ASSERT(entry.is_directory(), "Path %s does not lead to directory", shadersFolderPath.c_str())

    std::vector<std::filesystem::path> shadersPath;
    CollectItemsPath(shadersPath, shadersFolderPath);

    for(std::filesystem::path path : shadersPath) {
        std::string pathAsString = path.string();
        std::string fileName = path.filename().string();

        std::stringstream stream = ReadFile(pathAsString);
        resSys->RegisterResource<ResourceShader>(fileName, ParseFile(stream));
        LOG("finished loading %s", fileName.c_str())
    }
}

std::stringstream ShaderLoader::ReadFile(std::string path) {
    std::stringstream shaderSourceStream;

    std::ifstream fileStream;
    fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);

    try {
        fileStream.open(path, std::ifstream::binary);	
    }
    catch(std::ifstream::failure e) {
        ASSERT_FAIL("Can not load shader by path %s. Reason: %s", path.c_str(), e.what())
    }

    fileStream.seekg (0, fileStream.end);
    int fileLength = fileStream.tellg();
    fileStream.seekg (0, fileStream.beg);

    try {
        shaderSourceStream << fileStream.rdbuf();
    }
    catch (std::ifstream::failure e) {
        ASSERT_FAIL("Can not read file %s. Reason: %s", path.c_str(), e.what())
    }

    std::string line;

    fileStream.close();

    return shaderSourceStream;
}

ResourceShader* ShaderLoader::ParseFile(std::stringstream& shaderSourceStream) {
    ResourceShader* resource = new ResourceShader();

    ShaderType type;
    std::string line;
    bool isAttributeSection = false;

    resource->shaderSources = new std::string[(int)(ShaderType::Count)];
    while (getline(shaderSourceStream, line)) {
        if (line.find("#type") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::Vertex;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::Fragment;
            } else {
                std::cout << "Undefined shader type in string: " << line << "\n";
            }

            continue;
        }

        if (!isAttributeSection && line.find("#attributes") != std::string::npos) {
            isAttributeSection = true;
            continue;
        } else if (isAttributeSection && line.find("attributes_end") != std::string::npos) {
            isAttributeSection = false;
            continue;
        }

        resource->shaderSources[(int)type].append(line + "\n");

        if (isAttributeSection) {
            bool isAttributeFound = false;
            for (auto& attribute: attributes) {
                if (line.find(attribute) != std::string::npos){
                    resource->attributeTypes.push_back(attribute);

                    isAttributeFound = true;
                    break;
                }
            }

            ASSERT(isAttributeFound, "Unkonwn attribute type in line %s", line.c_str())
        }
    }

    return resource;
}