#include "VertexBuffer.h"
#include "renderer.h"
#include <iostream>
VertexBuffer::VertexBuffer(float data[], unsigned int size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1,&id);
}

void VertexBuffer::updateVertexBuffer(void* data, unsigned int size)
{
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);

}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
