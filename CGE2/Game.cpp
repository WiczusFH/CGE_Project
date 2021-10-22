#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <GL/GL.h>
#include <gl/GLU.h>
#include <glut.h>
#include <fstream>
#include <streambuf>


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

std::string XreadFile(const char* filepath) {
    std::ifstream t(filepath);
    std::string str((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
    return str;
}

int main(void)
{
    GLFWwindow* window;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

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

    float Vertices[] = {
        -0.5f,-0.5f,    //0
        0.5f, -0.5f,   //1
        0.5f, 0.5f,    //2
        -0.5f, 0.5f     //3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int buffer;
    unsigned int ibo;
    unsigned int shader = CreateShader(XreadFile("shaders/vertex.shader"), XreadFile("shaders/fragment.shader")); //-R shaderlocations


    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), Vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    

    glUseProgram(shader);
    
    float r = 0.0;
    float increment = 0.05f;
    int location = glGetUniformLocation(shader, "u_Color");
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
        glUniform4f(location, r, 0.5, 0.1, 1.0);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}




