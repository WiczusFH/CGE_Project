#include "Renderer.h"
#include "Shader.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertex_shader_path, const char* fragment_shader_path)
{
    id = CreateShader(vertex_shader_path, fragment_shader_path);

    glUseProgram(id);
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

void Shader::Bind() const
{
    glUseProgram(id);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(id, name.c_str());
    if (location == -1)
        std::cout << "No active uniform variable with name " << name << " found" << std::endl;

    m_UniformLocationCache[name] = location;

    return location;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3)
{
    glUniform4f(GetUniformLocation(name), f0, f1, f2, f3);
}

void Shader::SetUniformMat4f(const std::string& name, float value[])
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_TRUE, &value[0]);
}

//enum ShaderType
//{
//    NONE = -1, VERTEX = 0, FRAGMENT = 1
//};

std::string XreadFile(const char* filepath) {
    std::ifstream t(filepath);
    std::string str((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
    return str;
}


unsigned int Shader::CompileShader(GLenum type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    int result;
    int lenght;

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)alloca(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

unsigned int Shader::CreateShader(const char* vertexShader, const char* fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, XreadFile(vertexShader));
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, XreadFile(fragmentShader));
    glAttachShader(program, vs);
    glDeleteShader(vs); // -R with Detatch
    glAttachShader(program, fs);
    glDeleteShader(fs); // -R with Detatch
    glLinkProgram(program);
    return program;
}