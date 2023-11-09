#pragma once
#ifndef RECT_H
#define RECT_H

#include <glad.h>
#include <stb_image.h>
#include <vec3.h>
#include "shader.h"

class Voxel
{
    unsigned int VAO, EBO;
    unsigned int[] VBO;
    Shader* shader;
    vec3f position;
public:
    Voxel(const char* image_path, Shader* shader, vec3f _position);
    void draw();
};

#endif /* RECT_H */