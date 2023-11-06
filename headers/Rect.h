#pragma once
#ifndef RECT_H
#define RECT_H

#include <glad.h>
#include <stb_image.h>
#include <vec/vec2.h>
#include <vec/vec3.h>
#include <vec/vec4.h>
#include "Shader.h"

class Rect
{
    unsigned int VAO, VBO, EBO;
    Shader* shader;
public:
    Rect(const char* image_path, Shader* shader);
    void draw(float x);
};

#endif /* RECT_H */