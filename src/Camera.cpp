#include "Camera.h"
#include <iostream>

Camera::Camera()
{
    position = vec3f(0.0f, 0.0f, 3.0f);
    yaw = 0.0f;
    pitch = 0.0f;
    fov = 0.785398;
    turn(0, 0);
}

void Camera::turn(float x_offset, float y_offset)
{
    yaw += x_offset;
    pitch += y_offset;

    if(pitch > 1.56)
        pitch = 1.56;
    if(pitch < -1.56)
        pitch = -1.56;

    direction.x = cos(yaw) * cos(pitch);
    direction.y = sin(pitch);
    direction.z = sin(yaw) * cos(pitch);
    direction = normalize(direction);

    update();
}

void Camera::update()
{
    vec3f y_axis = vec3f(0.0f, 1.0f, 0.0f);
    right = normalize(y_axis * direction);
    up = direction * right;
}
