#pragma once

#include "resource_system/resource/resource.h"

struct ResourceTexture : public Resource {
    INIT_RESOURCE(ResourceTexture)

    unsigned char* data;
    int width, height, nrChannels;
};