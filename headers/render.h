#pragma once
#ifndef RENDER_H
#define RENDER_H

void bindVAO(unsigned int ID);
void bindVBO(unsigned int ID);
void bindVBOData(int size, const float* data);
void bindTexture(unsigned int ID);
void bindTextureData(const char* image_path);

#endif /* RENDER_H */