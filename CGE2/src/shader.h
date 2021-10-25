#pragma once

#include <string>
#include <unordered_map>
#include <GLFW/glfw3.h>

struct ShaderProgramSource
{
};

class Shader
{
private:
    unsigned int id;
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const char* vertex_shader_path, const char* fragment_shader_path);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set uniforms
    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);
    void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
    void SetUniformMat4f(const std::string& name, float value[]);
private:
    int GetUniformLocation(const std::string& name);

    unsigned int CompileShader(GLenum type, const std::string& source);
    unsigned int CreateShader(const char* vertexShader, const char* fragmentShader);

};