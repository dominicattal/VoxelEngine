#pragma once
#ifndef VOXEL_H
#define VOXEL_H

#include <glad.h>
#include <unordered_map>
#include "vec3.h"
#include "shader.h"

class Voxel
{
    static unsigned int VAOs1[6], VBOs1[6], EBO1;
    unsigned int VAOs[6], VBOs[6], EBO;
    static int test;
    unsigned int modelID, texture;
    Shader* shader;
    vec3f position;
    std::unordered_map<vec3f, Voxel*>* voxels;
public:
    Voxel(Shader* shader_, vec3f position_, std::unordered_map<vec3f, Voxel*>* voxels_, unsigned int texture_);
    void draw();
    static void initalize();
};

#endif /* VOXEL_H */