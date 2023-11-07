#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include <vec/vec3.h> 

class Camera
{
public:
    float fov, yaw, pitch;
    vec3f position;
    vec3f direction;
    vec3f right;
    vec3f up;
    Camera();
    void turn(float x_offset, float y_offset);
    void update();
};

#endif /* CAMERA_H */