#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <GL/GL.h>
#include <gl/GLU.h>
#include <glut.h>
#include <fstream>
#include <streambuf>
#include "Libs/stb_image.h"

#include "src/renderer.h"
#include "src/VertexBuffer.h"
#include "src/IndexBuffer.h"
#include "src/VertexArray.h"
#include "src/shader.h"
#include "src/renderer.h"
#include "src/Textures.h"
#include "src/models//ship.h"
#include "src/Physics.h"
#include "src/models/AsteroidStrip.h"
#include "src/models/Space.h"
#include "src/models/Asteroid.h"
#include "src/Camera.h"
#include <list>
#include <iterator>

#pragma region Globals
const char* VERTEX_SHADER_LOCATION = "shaders/vertex.shader";
const char* FRAGMENT_SHADER_LOCATION = "shaders/fragment.shader";
//float SCREEN_POSITION=0;
float TARGET_FPS = 60.0;
float SCROLL_SPEED = 0.01;
//float CAMERA_POS_X = 0;

#pragma endregion
bool aliveObject[99] = { false, true, true, true, true };

Ship* ship;
AsteroidStrip* stripUp;
AsteroidStrip* stripDown;
std::list<Asteroid> asteroidList;

//List<World> list
#pragma region Keyboard
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == 1) {
        exit(0);
    }

    if(aliveObject[1]){
        if (key == GLFW_KEY_W && action >= 1) { ship->DirectionActive[1] = 1; }
        if (key == GLFW_KEY_A && action >= 1) { ship->DirectionActive[0] = -1; }
        if (key == GLFW_KEY_S && action >= 1) { ship->DirectionActive[1] = -1; }
        if (key == GLFW_KEY_D && action >= 1) { ship->DirectionActive[0] = 1; }

        if (key == GLFW_KEY_W && ship->DirectionActive[1] == 1 && action == 0) { ship->DirectionActive[1] = 0; }
        if (key == GLFW_KEY_A && ship->DirectionActive[0] == -1 && action == 0) { ship->DirectionActive[0] = 0; }
        if (key == GLFW_KEY_S && ship->DirectionActive[1] == -1 && action == 0) { ship->DirectionActive[1] = 0; }
        if (key == GLFW_KEY_D && ship->DirectionActive[0] == 1 && action == 0) { ship->DirectionActive[0] = 0; }
    }
    if (key == GLFW_KEY_R) {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        std::cout << width << std::endl;
        std::cout << height << std::endl;
    }
};

int objToObjIndex(std::string name) {
    if (!name.compare("ship")) { return 1; }
    return 0;
}

#pragma endregion
int main(int argc, char* argv[])
{
#pragma region window and glfw


    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    int width_asp, height_asp;
    glfwGetMonitorPhysicalSize(monitor, &width_asp, &height_asp);
    float window_width, window_height;
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    window_width = mode->width;
    window_height = mode->height;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(window_width, window_height, "Game", glfwGetPrimaryMonitor(), NULL);
    //window = glfwCreateWindow(600, 300, "Game", NULL, NULL);
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(10);
    glfwSetKeyCallback(window, keyboard);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error! " << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl; // -R


#pragma endregion
#pragma region Pointers and Setup for Rendering 
    //Pointers
    Shader shader(VERTEX_SHADER_LOCATION, FRAGMENT_SHADER_LOCATION);
    VertexBufferLayout vertexBufferLayout;
    Renderer renderer;
    Camera camera(window_height / window_width);
    shader.Bind();
    camera.addShader(shader);
    camera.setProjection();
    vertexBufferLayout.Push<float>(2,2); //S
    vertexBufferLayout.Push<float>(2,2); //S
    //Blending

    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE_MINUS_CONSTANT_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float identityMatrix[16] = {
    1,0,0,0,
    0,1,0,0,
    0,0,0,0,
    0,0,0,1
    };
    shader.SetUniformMat4f("u_ROT", identityMatrix);
    shader.SetUniformMat4f("u_CEN", identityMatrix);
#pragma region Main Loop
#pragma region Object Initalisation

    Space space(shader, renderer, vertexBufferLayout, 50);
    ship = new Ship(shader, renderer, vertexBufferLayout, 1);
    stripUp = new AsteroidStrip(shader, renderer, vertexBufferLayout,0.9,0.1,50, 0,3);
    stripDown = new AsteroidStrip(shader, renderer, vertexBufferLayout,-0.85, 0.15,50, 0.5, 4);

    //Asteroids /-R make a file with this
    asteroidList.push_back(Asteroid(shader, renderer,vertexBufferLayout, 1,0,0.12,0,3));
    asteroidList.push_back(Asteroid(shader, renderer,vertexBufferLayout, 1.1,-0.3,0.08,0,3));
    asteroidList.push_back(Asteroid(shader, renderer,vertexBufferLayout, 1.3,0.3,0.12,0,3));
    asteroidList.push_back(Asteroid(shader, renderer,vertexBufferLayout, 1.5,0.3,0.12,1,3));
    asteroidList.push_back(Asteroid(shader, renderer,vertexBufferLayout, 2.0,0.5,0.12,1,3));
    asteroidList.push_back(Asteroid(shader, renderer,vertexBufferLayout, 2.1,-0.6,0.12,1,3));
    asteroidList.push_back(Asteroid(shader, renderer,vertexBufferLayout, 2.7,0.05,0.4,2,3));
    asteroidList.push_back(Asteroid(shader, renderer,vertexBufferLayout, 5.0,-0.6,0.20,1,3));
    asteroidList.push_back(Asteroid(shader, renderer,vertexBufferLayout, 5.4,-0.4,0.25,0,1));
    asteroidList.push_back(Asteroid(shader, renderer,vertexBufferLayout, 5.8,0.0,0.25,0,2));
    asteroidList.push_back(Asteroid(shader, renderer,vertexBufferLayout, 6.0,0.4,0.15,1,2));

    double lasttime = glfwGetTime();
#pragma endregion
    while (!glfwWindowShouldClose(window))
    {
        //Fix FPS
        while (glfwGetTime() < lasttime + 1.0 / TARGET_FPS) {}
        lasttime += 1.0 / TARGET_FPS;

        //scroll the screen
        if (aliveObject[1]) { camera.scrollX(SCROLL_SPEED); }
        shader.Bind();
        camera.setView();

        //UpdateShipPosition

        if (aliveObject[1]) { ship->movement(camera.getX()-1); }

        //IsHittingStrip
        if (aliveObject[1]) {
            if (CheckCollision(ship->getCollisionBox(), stripUp->getCollisionBox())||
                CheckCollision(ship->getCollisionBox(), stripDown->getCollisionBox())) 
            {aliveObject[1] = false; delete ship;}
        }

        //IsHitting Asteroids
        if (aliveObject[1]) {
            for (std::list<Asteroid>::iterator asteroid_iterator = asteroidList.begin(); asteroid_iterator != asteroidList.end(); ++asteroid_iterator) {
                if (CheckCollision(ship->getCollisionBox(), asteroid_iterator->getCollisionBox()) ||
                    CheckCollision(ship->getCollisionBox(), asteroid_iterator->getCollisionBox()))
                {
                    aliveObject[1] = false; delete ship;
                    break;
                }
            }
        }



        //render
        glClear(GL_COLOR_BUFFER_BIT);
        //Backgrounds

        space.sendToRenderer();

        //Conditional Rendering
        if (aliveObject[1]) { ship->sendToRenderer(); } 
        
        for (std::list<Asteroid>::iterator asteroid_iterator = asteroidList.begin(); asteroid_iterator != asteroidList.end(); ++asteroid_iterator) {
            asteroid_iterator->updateAsteroid();
            asteroid_iterator->sendToRenderer();
        }
        //Reset rotation after asteroids
        shader.SetUniformMat4f("u_ROT", identityMatrix);
        shader.SetUniformMat4f("u_CEN", identityMatrix);
        shader.SetUniformMat4f("u_CENI", identityMatrix);


        stripUp->sendToRenderer();
        stripDown->sendToRenderer();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
#pragma endregion

    glfwTerminate();
    return 0;
}




