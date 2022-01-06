#ifndef VERTEX_ARRAY_OBJECT
#define VERTEX_ARRAY_OBJECT

#include "common.h"

class VertexArrayObject
{
private:
    unsigned int id;

public:
    VertexArrayObject();

    void Bind();
    void UnBind();    
};



#endif