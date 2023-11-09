#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include <vec3.h> 

class Camera
{
public:
    float fov, yaw, pitch;
    float speed, sensitivity;
    vec3f position;
    vec3f facing, right, up;
    Camera();
    void turn(float x_offset, float y_offset);
    void move(vec3f direction, float dt);
    void update();
};

#endif /* CAMERA_H */