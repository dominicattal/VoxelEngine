#pragma once
#ifndef VAO_H
#define VAO_H

#include <glad.h>

class VAO
{
    unsigned int ID;
public:
    VAO();
    void bind();
};

#endif /* VAO_H */