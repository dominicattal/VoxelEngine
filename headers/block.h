#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <map>
#include <unordered_map>
#include "shader.h"
#include "render.h"
#include "vec3.h"

enum Blocktype
{
    TYPE1, TYPE2
};

struct Block
{
    unsigned int VAOs[6], VBOs[6], TEXs[6];
    Block();
};

void initalizeBlocks();
void drawBlocks();

#endif /* BLOCK_H */