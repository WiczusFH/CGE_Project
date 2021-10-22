#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "renderer.h"
#include <iostream>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererId);

}

void VertexArray::AddBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& layout)
{
	Bind();
	vertexBuffer.Bind();
	unsigned int offset = 0;
	const auto& elements = layout.GetElements();
	for (int i = 0; i < elements.size();i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.vertex_count, element.type, element.normalized, layout.GetStride() * element.vertex_count, (const void*) offset);
		offset += element.vertex_count*VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind()
{
	glBindVertexArray(m_RendererId);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);

}
