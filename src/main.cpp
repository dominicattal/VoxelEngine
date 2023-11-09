#include <glad.h>
#include <glfw.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_map>

#include "vec3.h"
#include "error.h"
#include "shader.h"
#include "camera.h"
#include "voxel.h"

void processInput(GLFWwindow* window);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseButtonCallback(GLFWwindow* window, int button, int actions, int mods);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void updateProjectionMatrix(Shader shader);
void updateViewMatrix(Shader shader);
void updateDeltaTime();

int window_width  = 800;
int window_height = 600;
float dt = 0, frame_time;
Camera camera;

float mouse_x = window_width / 2;
float mouse_y = window_height / 2;

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
    glEnable(GL_CULL_FACE); 
    glCullFace(GL_FRONT); 

    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);  
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseCallback);  

    Shader shader("shaders/vertex.sl", "shaders/fragment.sl");
    updateProjectionMatrix(shader);

    std::unordered_map<vec3f, Voxel*> voxels;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                vec3f pos(i, j, k);
                voxels[pos] = new Voxel("assets/test.jpg", &shader, pos, &voxels);
            }
        }
    }
    voxels[vec3f(-5, 0, 0)] = new Voxel("assets/test.jpg", &shader, vec3f(-5, 0, 0), &voxels);

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
        for (auto pair : voxels)
            pair.second->draw();
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
    vec3f moving;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        moving.z += 1;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        moving.z -= 1;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        moving.x -= 1;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        moving.x += 1;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        moving.y -= 1;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        moving.y += 1;
    camera.move(moving, dt);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // Change viewport when window resized
    glViewport(0, 0, width, height);
    window_width = width;
    window_height = height;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        std::cout << 1 / dt << std::endl;
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        std::cout << 1 / dt << std::endl;
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    float x_offset = mouse_x - xpos;
    float y_offset = mouse_y - ypos;
    mouse_x = xpos;
    mouse_y = ypos;
    camera.turn(x_offset, y_offset);
}

void updateProjectionMatrix(Shader shader)
{
    shader.use();
    float aspect_ratio = (float)window_width / window_height;
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
    dx = camera.facing.x; dy = camera.facing.y; dz = camera.facing.z;
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
