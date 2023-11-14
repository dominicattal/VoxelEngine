#pragma once
#ifndef VOXEL1_H
#define VOXEL1_H

#include <map>
#include <unordered_map>
#include "shader.h"
#include "render.h"
#include "vec3.h"

enum Type
{
    TYPE1, TYPE2
};

struct Voxel
{
    unsigned int VAOs[6], VBOS[6];
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

int totalFaces();
void initalizeVoxels();
void createVoxel(vec3f position);
void updateVoxels(vec3f position);
void updateVertexData();
void drawVoxels();
void updateTopFaces(vec3f pos, int idx);

#endif /* VOXEL1_H */