#pragma once
#include <Vector>
#include <GL/glew.h>

class VertexBuffer {
private:
	unsigned int m_RendererId;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void updateVertexBuffer(const void* data, unsigned int size);
	void Bind();
	void Unbind();
};


