#include "model_loader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

#include "core/glm_declarations.h"

#include "resource_system/resource/resource_mesh.h"
#include "resource_system/resource/resource_material.h"

#include "resource_system/resource_system.h"
#include "core/asserts.h"
#include "core/logging.h"

static std::string modelsRoot = "\\assets\\models\\";

void ModelLoader::Load() {
    std::string modelsFolderPath = resSys->GetRoot() + modelsRoot;

    LOG("Load models from folder %s", modelsFolderPath.c_str())

    std::filesystem::directory_entry entry{modelsFolderPath};
    ASSERT(entry.exists(), "Directory %s does not exist", modelsFolderPath.c_str())
    ASSERT(entry.is_directory(), "Path %s does not lead to directory", modelsFolderPath.c_str())

    std::vector<std::filesystem::path> modelsPath;
    CollectItemsPath(modelsPath, modelsFolderPath);

    Assimp::Importer importer;

    for(std::filesystem::path path : modelsPath) {
        const aiScene* scene = importer.ReadFile(path.string(), 0);
        ASSERT(scene != nullptr, "Failed to open model by path %s: %s", path.c_str(), importer.GetErrorString())
        
        ResourceMesh* meshResource = new ResourceMesh();

        const aiMesh* mesh = scene->mMeshes[0];

        for(int idx = 0; idx < mesh->mNumVertices; ++idx) {
            aiVector3D vert = mesh->mVertices[idx];
            aiVector3D normal = mesh->mNormals[idx];
            aiVector3D uv = mesh->mTextureCoords[0][idx];

            meshResource->verticies.push_back( {
                glm::vec3(vert.x, vert.y, vert.z),
                glm::vec3(normal.x, normal.y, normal.z),
                glm::vec2(uv.x, uv.y)
            } );
        }

        for(int idx = 0; idx < mesh->mNumFaces; ++idx) {
            aiFace& face = mesh->mFaces[idx];

            for(int i = 0; i < face.mNumIndices; ++i) {
                meshResource->indices.push_back(face.mIndices[i]);
            }
        }

        const int matIdx = mesh->mMaterialIndex;
        if (matIdx >= 0) {
            ResourceMaterial* resourceMaterial = new ResourceMaterial();

            aiMaterial* mat = scene->mMaterials[matIdx];

            aiString textureName;
            aiString materialName;
            mat->Get(AI_MATKEY_NAME, materialName);
            mat->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), textureName);

            resourceMaterial->textureName = textureName.C_Str();
            resSys->RegisterResource(materialName.C_Str(), resourceMaterial);

            meshResource->materialName = materialName.C_Str();
        }

        std::string fileName = path.filename().string();
        resSys->RegisterResource(fileName, meshResource);
        LOG("finished loading %s", fileName.c_str())
    }
}