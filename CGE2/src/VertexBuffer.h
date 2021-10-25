#pragma once
#include <Vector>
#include <GL/glew.h>

class VertexBuffer {
private:
	unsigned int id;
public:
	VertexBuffer(float data[], unsigned int size);
	~VertexBuffer();

	void updateVertexBuffer(void* data, unsigned int size);
	void Bind();
	void Unbind();
};


