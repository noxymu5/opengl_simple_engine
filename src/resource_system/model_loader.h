#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <string>

#include "resource_system/mesh_resource.h"

class ModelLoader {
public:
    ModelLoader(std::string path);
    MeshResource Get();

private:
    MeshResource resource;
};

#endif