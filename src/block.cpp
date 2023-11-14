#include "block.h"
#include <iostream>

std::unordered_map<vec3f, Block*>* blocks = new std::unordered_map<vec3f, Block*>();
std::unordered_map<blocktype, TypeTextures>* textures = new std::unordered_map<blocktype, TypeTextures>();

/*
unsigned int tex2;
    bindTexture(tex2);
    bindTextureData("assets/test.jpg");
*/

void initalizeBlocks()
{
    for (int type = 0; type <= 1; type++)
    {
        TypeTextures type_texs;
        textures->insert({static_cast<blocktype>(type), type_texs});
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 10; k++)
            {
                createBlock(vec3f(i, -j-1, k));
            }
        }
    }
}

void drawBlocks()
{

}

void createBlock(vec3f loc)
{

}

Block::Block(blocktype type_)
{
    type = type_;
}

TypeTextures::TypeTextures()
{

}