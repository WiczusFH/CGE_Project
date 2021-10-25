#include "renderer.h"
#include <iostream>

void Renderer::Draw(VertexArray& vertexArray, IndexBuffer& indexBuffer, Shader& shader)
{
	
	vertexArray.Bind();
	indexBuffer.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
