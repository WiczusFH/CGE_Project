#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "renderer.h"
#include <iostream>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &id);

}

void VertexArray::AddBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& layout)
{
	Bind();
	vertexBuffer.Bind();
	unsigned int offset = 0;
	auto& elements = layout.GetElements();
	for (int i = 0; i < elements.size();i++) {
		auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.post_count, element.type, element.normalized, layout.GetStride() * element.attrib_count, (const void*) offset);
		offset += element.attrib_count*sizeof(element.type);
	}
}

void VertexArray::Bind()
{
	glBindVertexArray(id);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);

}
