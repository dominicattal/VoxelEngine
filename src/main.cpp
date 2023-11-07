#include <glad.h>
#include <glfw.h>
#include <iostream>
#include <cmath>
#include <vec/vec2.h>
#include <vec/vec3.h>
#include <vec/vec4.h>
#include "error.h"
#include "Shader.h"
#include "Camera.h"
#include "Rect.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int actions, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void updateProjectionMatrix(Shader shader);
void updateViewMatrix(Shader shader);
void updateDeltaTime();

int window_width  = 800;
int window_height = 800;
float dt = 0, frame_time;
Camera camera;

int mouse_x = window_width / 2;
int mouse_y = window_height / 2;

int main() 
{
    // initialize glfw
    if (!glfwInit())
        throwError(1);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // initalize window
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Voxels", NULL, NULL);
    if (window == NULL)
        throwError(2);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

    // initalize glad
    if (!gladLoadGL(glfwGetProcAddress))
        throwError(3);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);  

    Shader shader("shaders/vertex.sl", "shaders/fragment.sl");
    updateProjectionMatrix(shader);

    Rect square("assets/test.jpg", &shader);

    frame_time = glfwGetTime();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        updateViewMatrix(shader);
        square.draw();
        updateDeltaTime();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 1;
}

void processInput(GLFWwindow* window)
{
    // Handles keyboard inputs
    float move_speed = 0.5;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.position.y -= move_speed * dt;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.position.y += move_speed * dt;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.position.x += move_speed * dt;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.position.x -= move_speed * dt;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.position.z -= move_speed * dt;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.position.z += move_speed * dt;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Change viewport when window resized
    glViewport(0, 0, width, height);
    window_width = width;
    window_height = height;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        std::cout << 1 / dt << std::endl;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        std::cout << 1 / dt << std::endl;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    float xoffset = mouse_x - xpos;
    float yoffset = mouse_y - ypos;
    mouse_x = xpos;
    mouse_y = ypos;

    float sensitivity = 0.001f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.turn(xoffset, yoffset);
}

void updateProjectionMatrix(Shader shader)
{
    // update shader projection matrix
    shader.use();
    float aspect_ratio = window_width / window_height;
    float fov = camera.fov;
    float near_clip_dis = 0.1f; 
    float far_clip_dis = 100.0f; 
    float v1, v2, v3, v4;
    v1 = 1 / (aspect_ratio * tan(fov / 2));
    v2 = 1 / (tan(fov / 2));
    v3 = (-near_clip_dis - far_clip_dis) / (near_clip_dis - far_clip_dis);
    v4 = (2 * far_clip_dis * near_clip_dis) / (near_clip_dis - far_clip_dis);
    const float proj[] = {
        v1, 0, 0, 0,
        0, v2, 0, 0,
        0, 0, v3, 1,
        0, 0, v4, 0
    };
    unsigned int projID = glGetUniformLocation(shader.ID, "perspective");
    glUniformMatrix4fv(projID, 1, GL_FALSE, proj);
}

void updateViewMatrix(Shader shader)
{
    shader.use();
    float rx, ry, rz; 
    float ux, uy, uz; 
    float dx, dy, dz; 
    float px, py, pz; 
    float k1, k2, k3;
    rx = camera.right.x; ry = camera.right.y; rz = camera.right.z;
    ux = camera.up.x; uy = camera.up.y; uz = camera.up.z;
    dx = camera.direction.x; dy = camera.direction.y; dz = camera.direction.z;
    px = -camera.position.x; py = -camera.position.y; pz = -camera.position.z;
    k1 = px * rx + py * ry + pz * rz;
    k2 = px * ux + py * uy + pz * uz;
    k3 = px * dx + py * dy + pz * dz;
    float view[] = {
        rx, ux, dx, 0,
        ry, uy, dy, 0,
        rz, uz, dz, 0,
        k1, k2, k3, 1
    };
    unsigned int viewID = glGetUniformLocation(shader.ID, "view");
    glUniformMatrix4fv(viewID, 1, GL_FALSE, view);
}

void updateDeltaTime()
{
    float current_time = glfwGetTime();
    dt = current_time - frame_time;
    frame_time = current_time;
}
