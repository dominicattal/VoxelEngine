#include "block.h"
#include <iostream>

std::unordered_map<vec3f, Block*>* blocks = new std::unordered_map<vec3f, Block*>();
std::unordered_map<blocktype, TypeTextures>* textures = new std::unordered_map<blocktype, TypeTextures>();

vec3f dirs[] = {
    vec3f(0, 0,  1),
    vec3f(0, 0, -1),
    vec3f(-1, 0, 0),
    vec3f( 1, 0, 0),
    vec3f(0,  1, 0),
    vec3f(0, -1, 0)
};

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
    blocks->insert({position, new Block(type)});
    updatePosition(position);
}

void updatePosition(vec3f position)
{
    if (blocks->count(position) > 0)
    {
        Block* block = blocks->at(position);
        TypeTextures texture = textures->at(block->type);
        texture.updateFace(position, TOP);
    }
}

Block::Block(blocktype type_)
{
    type = type_;
}

TypeTextures::TypeTextures()
{
    glGenVertexArrays(6, VAOs);
    glGenBuffers(6, VBOs);
    glGenTextures(6, TEXs);
    for (int i = 0; i < 6; i++)
    {    
        bindTexture(TEXs[i]);
        bindTextureData("assets/type1.png");
        vertex_data[i] = new float[0];
        faces[i] = new std::unordered_set<vec3f>();
    }
}

void TypeTextures::updateFace(vec3f position, Face face)
{
    std::unordered_set<vec3f>* face_data = faces[face];
    face_data->insert(position);
    delete[] vertex_data[face];
    int size = face_data->size();
    vertex_data[face] = new float[size * 6 * 5];

    int idx = 0;
    for (auto pos : *face_data)
    {
        vertex_data[face][idx]    = pos.x + 1;
        vertex_data[face][idx+1]  = pos.y + 1;
        vertex_data[face][idx+2]  = pos.z + 1;
        vertex_data[face][idx+3]  = 1.0;
        vertex_data[face][idx+4]  = 1.0;
        vertex_data[face][idx+5]  = pos.x + 1;
        vertex_data[face][idx+6]  = pos.y + 1;
        vertex_data[face][idx+7]  = pos.z;
        vertex_data[face][idx+8]  = 1.0;
        vertex_data[face][idx+9]  = 0.0;
        vertex_data[face][idx+10] = pos.x;
        vertex_data[face][idx+11] = pos.y + 1;
        vertex_data[face][idx+12] = pos.z + 1;
        vertex_data[face][idx+13] = 0.0;
        vertex_data[face][idx+14] = 1.0;
        vertex_data[face][idx+15] = pos.x + 1;
        vertex_data[face][idx+16] = pos.y + 1;
        vertex_data[face][idx+17] = pos.z;
        vertex_data[face][idx+18] = 1.0;
        vertex_data[face][idx+19] = 0.0;
        vertex_data[face][idx+20] = pos.x ;
        vertex_data[face][idx+21] = pos.y + 1;
        vertex_data[face][idx+22] = pos.z;
        vertex_data[face][idx+23] = 0.0;
        vertex_data[face][idx+24] = 0.0;
        vertex_data[face][idx+25] = pos.x;
        vertex_data[face][idx+26] = pos.y + 1;
        vertex_data[face][idx+27] = pos.z + 1;
        vertex_data[face][idx+28] = 0.0;
        vertex_data[face][idx+29] = 1.0;        
        idx += 30;
    }

    glBindVertexArray(VAOs[face]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[face]);
    glBufferData(GL_ARRAY_BUFFER, size * 6 * 5 * sizeof(float), vertex_data[face], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void TypeTextures::updateVertexData(Face face)
{
    
}

void TypeTextures::drawFaces()
{
    for (int i = 0; i < 6; i++)
    {
        bindVAO(VAOs[i]);
        bindTexture(TEXs[i]);
        drawTriangles(200 * 6);
    }
}
