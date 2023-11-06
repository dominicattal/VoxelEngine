#include <glad.h>
#include <glfw.h>
#include <iostream>
#include <vec/vec2.h>
#include <vec/vec3.h>
#include <vec/vec4.h>
#include "error.h"
#include "Shader.h"
#include "Rect.h"

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void updateDeltaTime();

int window_width  = 800;
int window_height = 800;
float dt = 0, frame_time;

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

    // initalize glad
    if (!gladLoadGL(glfwGetProcAddress))
        throwError(3);

    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    Shader shader("shaders/vertex.sl", "shaders/fragment.sl");
    
    Rect square;

    frame_time = glfwGetTime();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.use();
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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Change viewport when window resized
    glViewport(0, 0, width, height);
    window_width = width;
    window_height = height;
}

void updateDeltaTime()
{
    float current_time = glfwGetTime();
    dt = current_time - frame_time;
    frame_time = current_time;
}