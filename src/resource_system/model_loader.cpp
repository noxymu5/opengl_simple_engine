#include "model_loader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "core/glm_declarations.h"

#include "resource_system/resource_system.h"
#include "core/asserts.h"

ModelLoader::ModelLoader(std::string path) {
    ResourceSystem* resSys = ResourceSystem::Get();
    std::string resultPath = resSys->PathToModel(path);

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(resultPath, 
        aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
    ASSERT(scene != nullptr, "Failed to open model by path %s: %s", path.c_str(), importer.GetErrorString())
    
    const aiMesh* mesh = scene->mMeshes[0];

    for(int idx = 0; idx < mesh->mNumVertices; ++idx) {
        aiVector3D vert = mesh->mVertices[idx];
        aiVector3D normal = mesh->mNormals[idx];
        aiVector3D uv = mesh->mTextureCoords[0][idx];

        resource.verticies.push_back( {
            glm::vec3(vert.x, vert.y, vert.z),
            glm::vec2(uv.x, uv.y),
            glm::vec3(normal.x, normal.y, normal.z)
        } );
    }

    for(int idx = 0; idx < mesh->mNumFaces; ++idx) {
        aiFace& face = mesh->mFaces[idx];

        for(int i = 0; i < face.mNumIndices; ++i) {
            resource.indices.push_back(face.mIndices[i]);
        }
    }
}

MeshResource ModelLoader::Get() {
    return resource;
}