#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include <vec/vec3.h> 

class Camera
{
public:
    float fov;
    vec3f position;
    vec3f direction;
    vec3f right;
    vec3f up;
    Camera();
};

#endif /* CAMERA_H */