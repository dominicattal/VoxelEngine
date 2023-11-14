#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <map>
#include <unordered_map>
#include "shader.h"
#include "texture.h"
#include "vec3.h"

enum Blocktype
{
    TYPE1, TYPE2
};

struct Block
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
    
    Block();
};

void initalizeBlocks();
void drawBlocks();

#endif /* BLOCK_H */