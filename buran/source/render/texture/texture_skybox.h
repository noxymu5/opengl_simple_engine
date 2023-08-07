#pragma once

#include <string>

#include "texture_base.h"

class TextureSkybox : public TextureBase {
public:
    TextureSkybox(std::string textureName);

protected:
    virtual void BindTexture() override;
};