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
#include <list>
#include <iterator>
#include <thread>

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
#include "src/models/Laser.h"
#include "src/models/Win.h"

#pragma region Globals
const char* VERTEX_SHADER_LOCATION = "shaders/vertex.shader";
const char* FRAGMENT_SHADER_LOCATION = "shaders/fragment.shader";
float TARGET_FPS = 60.0;
float SCROLL_SPEED = 0.02;

#pragma endregion
bool aliveObject[99] = { false, true, true, true, true };

Ship* ship;
AsteroidStrip* stripUp;
AsteroidStrip* stripDown;

std::list<Asteroid> asteroidList;
std::list<Laser> laserList;






bool laserHit_AsteroidIterator(std::list<Laser>::iterator laser_iterator) {
    for (std::list<Asteroid>::iterator asteroid_iterator = asteroidList.begin(); asteroid_iterator != asteroidList.end();) {
        if (CheckCollision(laser_iterator->getCollisionBox(), asteroid_iterator->getCollisionBox())) {
            laserList.erase(laser_iterator);
            asteroidList.erase(asteroid_iterator);
            return true;
        }
        else {
            ++asteroid_iterator;
        }
    }
    return false;
}
void laserHit_LaserIterator() {
    for (std::list<Laser>::iterator laser_iterator = laserList.begin(); laser_iterator != laserList.end(); ) {
        if (laserHit_AsteroidIterator(laser_iterator)) {
            break;
        }
        else {
            ++laser_iterator;
        }
    }
}

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

        if (key == GLFW_KEY_SPACE && action == 1) { 
            if (ship->canShoot()) {
                ship->shoot();
                std::thread([]() { ship->loadNextShot();}).detach();
            }
        }
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
    //window = glfwCreateWindow(1200, 700, "Game", NULL, NULL);
    
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
    WinScreen winScreen(shader, renderer, vertexBufferLayout, 0.5);
    ship = new Ship(shader, renderer, vertexBufferLayout, laserList, 1);
    stripUp = new AsteroidStrip(shader, renderer, vertexBufferLayout,0.9,0.1,50, 0);
    stripDown = new AsteroidStrip(shader, renderer, vertexBufferLayout,-0.85, 0.15,50, 0.5);

    float scaleX = 0.2;
    float scaleY = 0.15;
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 14.3548 * scaleX, -3.4131 * scaleY, 0.25, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 19.5970 * scaleX, 3.5275 * scaleY, 0.25, 1, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 27.9910 * scaleX, -3.5111 * scaleY, 0.25, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 31.1918 * scaleX, 0.1470 * scaleY, 0.25, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 28.6279 * scaleX, 4.2950 * scaleY, 0.25, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 37.5772 * scaleX, 3.8051 * scaleY, 0.25, 1, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 40.6310 * scaleX, 1.3228 * scaleY, 0.25, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 42.3294 * scaleX, -0.9635 * scaleY, 0.25, 1, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 45.8569 * scaleX, -4.2460 * scaleY, 0.25, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 48.2738 * scaleX, -2.1883 * scaleY, 0.25, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 50.5112 * scaleX, -0.1633 * scaleY, 0.25, 1, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 53.7329 * scaleX, 4.2813 * scaleY, 0.25, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 46.1371 * scaleX, 3.9285 * scaleY, 0.25, 1, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 46.1371 * scaleX, 3.9285 * scaleY, 0.25, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 54.8147 * scaleX, -3.9259 * scaleY, 0.25, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 55.5201 * scaleX, -2.8207 * scaleY, 0.25, 1, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 54.5325 * scaleX, -0.2574 * scaleY, 0.07, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 57.2133 * scaleX, 2.2354 * scaleY, 0.07, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 38.8706 * scaleX, -4.0905 * scaleY, 0.07, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 20.2926 * scaleX, -4.0435 * scaleY, 0.07, 1, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 30.3106 * scaleX, -4.3727 * scaleY, 0.07, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 62.2929 * scaleX, -1.9976 * scaleY, 0.45, 2, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 67.6546 * scaleX, 3.9756 * scaleY, 0.25, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 70.6882 * scaleX, 2.1648 * scaleY, 0.25, 0, 1));
    asteroidList.push_back(Asteroid(shader, renderer, vertexBufferLayout, 73.7218 * scaleX, -0.5161 * scaleY, 0.25, 0, 1));

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

        //Is Ship Hitting Asteroids
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
        //Is laser hitting asteroids
        laserHit_LaserIterator();

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
        for (std::list<Laser>::iterator laser_iterator = laserList.begin(); laser_iterator != laserList.end(); ++laser_iterator) {
            laser_iterator->movement();
            laser_iterator->sendToRenderer();
        }

        stripUp->sendToRenderer();
        stripDown->sendToRenderer();
        if (camera.getX() > 17) {
            winScreen.updateX(camera.getX());
            winScreen.sendToRenderer();
        }
        if (camera.getX() > 19.5) {
            exit(0);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
#pragma endregion

    glfwTerminate();
    return 0;
}




