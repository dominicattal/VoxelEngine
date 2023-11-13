#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include <vec3.h> 
#include <shader.h>

struct Camera
{
    float yaw, pitch;
    float speed, sensitivity;
    float aspect_ratio, fov;
    vec3f position;
    vec3f facing, right, up;
    unsigned int viewID, projID;
    Camera();
    void linkShader(Shader shader);
    void turn(float x_offset, float y_offset);
    void move(vec3f direction);
    void updateViewMatrix();
    void updateProjectionMatrix();
};

#endif /* CAMERA_H */