#include "camera.h"
#include <iostream>

Camera::Camera()
{
    position = vec3f(0.0f, 0.0f, 3.0f);
    yaw = 0.0;
    pitch = 0.0;
    fov = 0.785398;
    sensitivity = 0.001;
    speed = 5;
    turn(0, 0);
}

void Camera::turn(float x_offset, float y_offset)
{
    yaw += x_offset * sensitivity;
    pitch += y_offset * sensitivity;

    if(pitch > 1.56)
        pitch = 1.56;
    if(pitch < -1.56)
        pitch = -1.56;

    facing.x = cos(yaw) * cos(pitch);
    facing.y = sin(pitch);
    facing.z = sin(yaw) * cos(pitch);
    facing = normalize(facing);

    update();
}

void Camera::move(vec3f moving, float dt)
{
    normalize(moving);
    vec3f direction;
    direction += right  * moving.x;
    direction += up     * moving.y;
    direction += facing * moving.z;
    direction = normalize(direction);
    position += direction * speed * dt;
}

void Camera::update()
{
    vec3f y_axis = vec3f(0.0f, 1.0f, 0.0f);
    right = normalize(y_axis * facing);
    up = facing * right;
}

