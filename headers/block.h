#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <unordered_map>
#include <unordered_set>
#include "shader.h"
#include "render.h"
#include "vec3.h"

enum blocktype
{
    TYPE1 = 0, 
    TYPE2 = 1
};

enum Face 
{
    LEFT   = 0,
    RIGHT  = 1,
    FRONT  = 2,
    BACK   = 3,
    TOP    = 4,
    BOTTOM = 5
};

struct Block
{
    blocktype type;
    Block(blocktype type_);
};

struct TypeTextures
{
    unsigned int VAOs[6], VBOs[6], TEXs[6], sizes[6];
    float* vertex_data[6];
    std::unordered_set<vec3f>* faces[6];
    TypeTextures();
    void updateFace(vec3f position, Face face);
    void updateVertexData(Face face);
    void drawFaces();
};

void initalizeBlocks();
void drawBlocks();
void createBlock(blocktype type, vec3f position);
void updatePosition(vec3f position);

#endif /* BLOCK_H */