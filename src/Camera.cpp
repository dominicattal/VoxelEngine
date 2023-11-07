#include "Camera.h"
#include <iostream>

Camera::Camera()
{
    position = vec3f(0.0f, 0.0f, 3.0f);
    yaw = 0.0;
    pitch = 0.0;
    fov = 0.785398;
    sensitivity = 0.001;
    speed = 0.5;
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

    direction.x = cos(yaw) * cos(pitch);
    direction.y = sin(pitch);
    direction.z = sin(yaw) * cos(pitch);
    direction = normalize(direction);

    update();
}

void Camera::move(Dir dir, float dt)
{
    switch (dir)
    {
        case LEFT:
            position -= right * dt;
            break;
        case RIGHT:
            position += right * dt;
            break;
        case UP:
            position += up * dt;
            break;
        case DOWN:
            position -= up * dt;
            break;
        case FORWARD:
            position += direction * dt;
            break;
        case BACKWARD:
            position -= direction * dt;
            break;
    } 
}

void Camera::update()
{
    vec3f y_axis = vec3f(0.0f, 1.0f, 0.0f);
    right = normalize(y_axis * direction);
    up = direction * right;
}
