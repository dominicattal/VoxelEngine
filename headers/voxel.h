#pragma once
#ifndef VOXEL1_H
#define VOXEL1_H

#include <map>
#include <unordered_map>
#include "shader.h"
#include "texture.h"
#include "vec3.h"

struct Voxel
{
    /*
    Texture texture_top;
    Texture texture_bottom;
    Texture texture_right;
    Texture texture_left;
    Texture texture_front;
    Texture texture_back;
    */
    Voxel();
};

void initalizeVoxels();
void linkVoxelShader(Shader shader);
void createVoxel(vec3f position);
void drawVoxel(vec3f position);
void drawVoxels();

#endif /* VOXEL1_H */