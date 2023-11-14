#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <map>
#include <unordered_map>
#include "shader.h"
#include "render.h"
#include "vec3.h"

enum blocktype
{
    TYPE1, TYPE2
};

struct Block
{
    blocktype type;
    Block();
};

void initalizeBlocks();
void drawBlocks();
void createBlock(vec3f loc);

#endif /* BLOCK_H */