#ifndef BUFFERS
#define BUFFERS

#include "core/common.h"

class VertexBuffer
{
private:
    unsigned int id;

public:
    VertexBuffer(const float* verticesData, const unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};

class IndexBuffer
{
private:
    unsigned int id;
    unsigned int count;

public:
    IndexBuffer(const unsigned int* indices, unsigned int size);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;
    unsigned int GetCount();
};


#endif