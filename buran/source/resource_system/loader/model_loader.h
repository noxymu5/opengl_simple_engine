#pragma once

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "resource_system/loader/resource_loader.h"
#include "resource_system/resource/resource_mesh.h"

class ModelLoader : public ResourceLoader {
public:
    ModelLoader(ResourceSystem* sys) : ResourceLoader(sys) {}
    virtual void Load() override;
private:
    void TraverseNodeHierarchy(ResourceMesh* resourceMesh, const aiNode* node, const aiScene* scene);
};