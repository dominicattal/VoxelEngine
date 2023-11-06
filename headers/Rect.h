#pragma once
#ifndef RECT_H
#define RECT_H

#include <glad.h>
#include <stb_image.h>

class Rect
{
    unsigned int VAO, VBO, EBO;
public:
    Rect(const char* image_path);
    void draw();
};

#endif /* RECT_H */