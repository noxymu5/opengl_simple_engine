#include "texture_to_screen_dumper.h"

#include "resource_system/resource_system.h"
#include "resource_system/resource/resource_shader.h"

TextureToScreenDumper::TextureToScreenDumper() {
    ResourceShader* res = ResourceSystem::Get()->GetResource<ResourceShader>("texture_buffer_to_screen.glsl");
    shader = new Shader(res);
}

void TextureToScreenDumper::DumpToScreen(Texture* texture) {
    quad.Draw(shader, texture);
}