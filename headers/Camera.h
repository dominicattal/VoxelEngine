#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include <vec/vec3.h> 
#include <vec/vec2.h>

enum Dir 
{
    LEFT, RIGHT, UP, DOWN, FORWARD, BACKWARD
};

class Camera
{
public:
    float fov, yaw, pitch;
    float speed, sensitivity;
    vec3f position;
    vec3f direction;
    vec3f right;
    vec3f up;
    Camera();
    void turn(float x_offset, float y_offset);
    void move(Dir dir, float dt);
    void update();
};

#endif /* CAMERA_H */