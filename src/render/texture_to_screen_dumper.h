#ifndef TEXTURE_TO_SCREEN_DUMPE_H
#define TEXTURE_TO_SCREEN_DUMPE_H

#include "render/geometry/screen_quad.h"
#include "render/texture.h"
#include "render/shader.h"

class TextureToScreenDumper {
public:
    TextureToScreenDumper();
    void DumpToScreen(Texture* texture);

private:
    ScreenQuad quad;
    Shader* shader;
};

#endif