#pragma once
#ifndef VOXEL_H
#define VOXEL_H

#include <glad.h>
#include <stb_image.h>
#include <unordered_map>
#include "vec3.h"
#include "shader.h"

class Voxel
{
    unsigned int VAOs[6], VBOs[6], EBO;
    unsigned int modelID, texture;
    Shader* shader;
    vec3f position;
    std::unordered_map<vec3f, Voxel*>* voxels;
public:
    Voxel(Shader* shader_, vec3f position_, std::unordered_map<vec3f, Voxel*>* voxels_, unsigned int texture_);
    void draw();
};

#endif /* VOXEL_H */