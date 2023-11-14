#include "block.h"

std::unordered_map<vec3f, Block*>* blocks = new std::unordered_map<vec3f, Block*>();
std::unordered_map<

void initalizeBlocks()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 100; k++)
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

Block::Block()
{
    
}