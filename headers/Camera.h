#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include <vec3.h> 
#include <shader.h>

struct Camera
{
    float fov, yaw, pitch;
    float speed, sensitivity;
    vec3f position;
    vec3f facing, right, up;
    unsigned int viewID;
    Camera();
    void linkShader(Shader shader);
    void turn(float x_offset, float y_offset);
    void move(vec3f direction, float dt);
    void updateViewMatrix();
};

#endif /* CAMERA_H */