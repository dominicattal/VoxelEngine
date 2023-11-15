#include "block.h"
#include <iostream>

std::unordered_map<vec3f, Block*>* blocks = new std::unordered_map<vec3f, Block*>();
std::unordered_map<blocktype, TypeTextures>* textures = new std::unordered_map<blocktype, TypeTextures>();

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
                createBlock(TYPE1, vec3f(i, -j-1, k));
            }
        }
    }
}

void drawBlocks()
{
    for (auto pair : *textures)
    {
        pair.second.drawFaces();
    }
}

void createBlock(blocktype type, vec3f position)
{

}

void updatePosition(vec3f position)
{

}

Block::Block(blocktype type_)
{
    type = type_;
}

TypeTextures::TypeTextures()
{
    faces = new std::unordered_set<vec3f>[6];
    glGenVertexArrays(6, VAOs);
    glGenBuffers(6, VBOs);
    glGenTextures(6, TEXs);
    for (int i = 0; i < 6; i++)
    {
        bindTexture(TEXs[i]);
        bindTextureData("assets/type1.png");
        sizes[i] = 0;
    }
}

void TypeTextures::updateFace(Face face)
{

}

void TypeTextures::drawFaces()
{
    for (int i = 0; i < 6; i++)
    {
        bindVAO(VAOs[i]);
        bindTexture(TEXs[i]);
        drawTriangles(sizes[i]);
    }
}