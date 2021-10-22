#include "renderer.h"
#include <iostream>

void Renderer::Draw(VertexArray& vertexArray, IndexBuffer& indexBuffer, Shader& shader)
{
	shader.Bind();
	vertexArray.Bind();
	indexBuffer.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(VertexArray& vertexArray, IndexBuffer& indexBuffer, Shader& shader, const std::string& name, float r, float g, float b, float a)
{

	shader.Bind();
	shader.SetUniform4f(name, r, g, b, a);
	vertexArray.Bind();
	indexBuffer.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
