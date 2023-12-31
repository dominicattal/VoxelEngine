#pragma once
#ifndef RENDER_H
#define RENDER_H

#include <glad.h>
#include <stb_image.h>
#include <iostream>

void bindVAO(unsigned int ID);
void bindVBO(unsigned int ID);
void bindVBOData(int size, const float* data);
void bindTexture(unsigned int ID);
void bindTextureData(const char* image_path);
void drawTriangles(int vertex_count);

#endif /* RENDER_H */