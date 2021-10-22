#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <GL/GL.h>
#include <gl/GLU.h>
#include <glut.h>
#include <fstream>
#include <streambuf>

#include "src/renderer.h"
#include "src/VertexBuffer.h"
#include "src/IndexBuffer.h"
#include "src/VertexArray.h"
#pragma region Shader


static unsigned int CompileShader(GLenum type, const std::string& source){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
     int result;
    int lenght;

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*) alloca(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);
        std::cout<< message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int CreateShader(const std::string & vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glDeleteShader(vs); // -R with Detatch
    glAttachShader(program, fs);
    glDeleteShader(fs); // -R with Detatch
    glLinkProgram(program);
    return program;
}
#pragma endregion

std::string XreadFile(const char* filepath) {
    std::ifstream t(filepath);
    std::string str((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
    return str;
}

int main(void)
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

    if (glewInit() != GLEW_OK) {
        std::cout << "Error! " << std::endl;
    }
    std::cout << glGetString(GL_VERSION) << std::endl; // -R
#pragma endregion

#pragma region Vertex Data Initialisation


    float Vertices[] = {
        -0.3,-0.3, 
        0.3, -0.3, 
        0.3, 0.3,    
        -0.3, 0.3
    };

    float Vertices2[] = {
        0.5, 0.5,
        1.0, 0.5,   
        1.0, 1.0,  
        0.5, 1.0   
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
#pragma endregion

#pragma region Pointers for Rendering 
    unsigned int shader = CreateShader(XreadFile("shaders/vertex.shader"), XreadFile("shaders/fragment.shader")); //-R shaderlocations
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    VertexArray vertexArray;
    
    VertexBuffer vertexBuffer(Vertices, sizeof(Vertices));

    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.Push<float>(2);
    vertexArray.AddBuffer(vertexBuffer, vertexBufferLayout);

    IndexBuffer indexBuffer(indices, sizeof(indices) / sizeof(unsigned int));

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    

    glUseProgram(shader);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#pragma endregion

#pragma region Data Manipulation


    float r = 0.0;
    float increment = 0.05f;
    int location = glGetUniformLocation(shader, "u_Color");
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
        Vertices[0] += increment/2;

        glUniform4f(location, r, 0.5, 0.1, 1.0);
        vertexBuffer.updateVertexBuffer(Vertices, sizeof(Vertices));
        vertexArray.Bind();
        vertexBuffer.Bind();
        indexBuffer.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glUniform4f(location, 1.0, 1.0, r, 1.0);
        vertexBuffer.updateVertexBuffer(Vertices2, sizeof(Vertices2));
        vertexArray.Bind();
        vertexBuffer.Bind();
        indexBuffer.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


        glfwSwapBuffers(window);

        glfwPollEvents();
    }
#pragma endregion

    glfwTerminate();
    return 0;
}




