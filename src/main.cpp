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
#include "texture.h"
#include "voxel.h"
#include "globals.h"

typedef std::pair<int, int> vec2i;
typedef std::unordered_map<vec3f, Voxel*> chunk;

void processInput(GLFWwindow* window);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseButtonCallback(GLFWwindow* window, int button, int actions, int mods);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void updateDeltaTime();

void createChunk(vec2i loc, Shader shader);
void drawChunk(vec2i loc, Shader shader);
void drawChunks(vec2i loc, Shader shader);

int window_width  = 800;
int window_height = 600;
int render_distance = 5;
float dt = 0, frame_time;
Camera camera;
std::unordered_map<vec2i, chunk*>* chunks;
unsigned int texture;


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

    // save render calls
    glEnable(GL_CULL_FACE); 
    glCullFace(GL_FRONT); 

    glViewport(0, 0, window_width, window_height);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);  
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseCallback);  

    Shader shader("shaders/vertex.sl", "shaders/fragment.sl");
    camera.linkShader(shader);

    Texture block_texture("assets/test.jpg");
    block_texture.use();

    Voxel::initalize();

    chunks = new std::unordered_map<vec2i, chunk*>();
    createChunk(vec2i(0, 0), shader);

    frame_time = glfwGetTime();

    glEnable(GL_DEPTH_TEST);
    int c = 0;

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        drawChunks(toChunkCoords(camera.position), shader);
        updateDeltaTime();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 1;
}

// -------------------------------
// function definitions
// -------------------------------

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
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    float x_offset = mouse_x - xpos;
    float y_offset = mouse_y - ypos;
    mouse_x = xpos;
    mouse_y = ypos;
    camera.turn(x_offset, y_offset);
}

void updateDeltaTime()
{
    float current_time = glfwGetTime();
    dt = current_time - frame_time;
    frame_time = current_time;
}

void createChunk(vec2i loc, Shader shader)
{
    chunk* voxels = new chunk();
    int x = loc.first, y = loc.second;
    for (int i = 0; i < chunk_size; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            for (int k = 0; k < chunk_size; k++)
            {
                vec3f pos(i + x * chunk_size, - 1 - j, k + y * chunk_size);
                Voxel* voxel = new Voxel(&shader, pos, voxels, texture);
                voxels->insert({pos, voxel});
            }
        }
    }
    chunks->insert({loc, voxels});
}

void drawChunk(vec2i loc, Shader shader)
{
    if (chunks->count(loc) == 0)
    {
        createChunk(loc, shader);
    }

    chunk* voxels = chunks->at(loc);
    for (auto pair : *voxels)
    {
        pair.second->draw();
    }
}

void drawChunks(vec2i loc, Shader shader)
{
    int x = loc.first, y = loc.second;
    for (int i = -render_distance; i < render_distance; i++)
    {
        for (int j = -render_distance / 2; j < render_distance / 2; j++)
        {
            drawChunk(vec2i(x + i, y + j), shader);
        }
    }
}