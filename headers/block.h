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

struct Block
{
    blocktype type;
    Block(blocktype type_);
};

struct TypeTextures
{
    unsigned int VAOs[6], VBOs[6], TEXs[6];
    std::unordered_map<vec3f, Block*>* left;
    std::unordered_map<vec3f, Block*>* right;
    std::unordered_map<vec3f, Block*>* front;
    std::unordered_map<vec3f, Block*>* back;
    std::unordered_map<vec3f, Block*>* top;
    std::unordered_map<vec3f, Block*>* bottom;
    TypeTextures();
};

void initalizeBlocks();
void drawBlocks();
void createBlock(vec3f loc);

#endif /* BLOCK_H */