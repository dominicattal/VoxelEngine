#pragma once
#ifndef RECT_H
#define RECT_H

#include <glad.h>
#include <stb_image.h>
#include <vec3.h>
#include "Shader.h"

class Rect
{
    unsigned int VAO, VBO, EBO;
    Shader* shader;
public:
    Rect(const char* image_path, Shader* shader, float aspect_ratio);
    void draw();
};

#endif /* RECT_H */