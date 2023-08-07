#pragma once

class VertexArrayObject
{
private:
    unsigned int id;

public:
    VertexArrayObject();

    void Bind();
    void UnBind();    
};