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
#pragma region Globals
const char* VERTEX_SHADER_LOCATION = "shaders/vertex.shader";
const char* FRAGMENT_SHADER_LOCATION = "shaders/fragment.shader";
const char* SHIP_PATH = "textures/spaceship.png";
#pragma endregion


#pragma region Keyboard
void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == 1) {
        exit(0);
    }
    if (key == GLFW_KEY_E) {
        std::cout << key <<" " << scancode << " " << action << " " << mods << " "<< std::endl;
    }
    if (key == 'w') {
    }
};

#pragma endregion
//-R Abstract this

int main(int argc, char* argv[])
{
#pragma region window and glfw


    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(10);
    //glutInit(&argc, argv);
    glfwSetKeyCallback(window, keyboard);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error! " << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl; // -R

    //glutKeyboardFunc(keyboard);

#pragma endregion

#pragma region Vertex Data Initialisation


    float Vertices[] = {
        -0.3,-0.3, 0.0, 0.0,
        0.3, -0.3, 1.0, 0.0,
        0.3, 0.3,  1.0, 1.0,
        -0.3, 0.3, 0.0, 1.0
    };

    float Vertices2[] = {
        0.5, 0.5, 0.0, 0.0,
        1.0, 0.5, 1.0, 0.0,
        1.0, 1.0, 1.0, 1.0,
        0.5, 1.0, 0.0, 1.0
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    float TextureCoordinate[] = {
        0.1
    };
#pragma endregion

#pragma region Pointers for Rendering 
    Shader shader(VERTEX_SHADER_LOCATION, FRAGMENT_SHADER_LOCATION);
    VertexArray vertexArray;
    VertexBuffer vertexBuffer(Vertices, sizeof(Vertices));
    VertexBufferLayout vertexBufferLayout;
    IndexBuffer indexBuffer(indices, sizeof(indices) / sizeof(unsigned int));
    Renderer renderer;
    shader.Bind();

    Texture texture(SHIP_PATH);
    //texture.Bind();

    vertexBufferLayout.Push<float>(2,2);
    vertexBufferLayout.Push<float>(2,2);
    vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);

#pragma endregion

#pragma region Data Manipulation
    float r = 0.0;
    float increment = 0.05f;
#pragma endregion

#pragma region Main Loop


    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if (r > 1.0) {
            increment = -0.05;
        }
        if (r < 0) {
            increment = 0.05;
        }
        r += increment;
        //Vertices[0] += increment/2;


        texture.Bind();
        
        shader.SetUniform1i("u_Texture", 0);
        vertexBuffer.updateVertexBuffer(Vertices, sizeof(Vertices));
        renderer.Draw(vertexArray, indexBuffer, shader);
        
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
#pragma endregion

    glfwTerminate();
    return 0;
}




