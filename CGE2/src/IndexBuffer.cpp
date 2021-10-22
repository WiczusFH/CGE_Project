#include "IndexBuffer.h"
#include "renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:index_count(count)
{
	glGenBuffers(1, &m_RendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1,&m_RendererId);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);

}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
