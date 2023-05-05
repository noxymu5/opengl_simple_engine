#include "shader_loader.h"

#include <fstream>

#include "resource_system/resource_system.h"
#include "core/asserts.h"

static std::vector<std::string> attributes {
    "vec2",
    "vec3"
};

ShaderLoader::ShaderLoader(std::string path) {
    std::string resultPath = ResourceSystem::Get()->PathToShader(path);
    ReadFile(resultPath);
    ParseFile();
}

void ShaderLoader::ReadFile(std::string path) {
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
}

void ShaderLoader::ParseFile() {
    ShaderType type;
    std::string line;
    bool isAttributeSection = false;

    resource.shaderSources = new std::string[(int)(ShaderType::Count)];
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

        resource.shaderSources[(int)type].append(line + "\n");

        if (isAttributeSection) {
            bool isAttributeFound = false;
            for (auto& attribute: attributes) {
                if (line.find(attribute) != std::string::npos){
                    resource.attributeTypes.push_back(attribute);

                    isAttributeFound = true;
                    break;
                }
            }

            ASSERT(isAttributeFound, "Unkonwn attribute type in line %s", line.c_str())
        }
    }
}