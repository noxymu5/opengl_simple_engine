#pragma once

#include "render/geometry/screen_quad.h"
#include "render/texture/texture.h"
#include "render/shader.h"

class TextureToScreenDumper {
public:
    TextureToScreenDumper();
    void DumpToScreen(Texture* texture);

private:
    ScreenQuad quad;
    Shader* shader;
};