#pragma once
#include "VertexBuffer.h"
#include "VertexLayout.h"

class VertexArray {
private:
	unsigned int m_RendererId;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vertexBuffer, VertexBufferLayout& layout);

	void Bind();
	void Unbind();
};
