#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <string>

class TextureLoader {
public:
    TextureLoader(std::string path);
    ~TextureLoader();

    unsigned char* Get() { return data; }
    int Width() { return width; }
    int Height() { return height; }
    int NChannels() { return nrChannels; }
private:
    unsigned char* data;
    int width, height, nrChannels;
};

#endif