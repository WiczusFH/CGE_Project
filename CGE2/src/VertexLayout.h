#pragma once
#include <GL/glew.h>
#include <Vector>
#include "VertexBuffer.h"

struct VertexBufferElement {
	unsigned int type;
	unsigned int attrib_count;
	unsigned int post_count;
	bool normalized;
};


class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout(): m_Stride(0) {};
	template<typename T>
	void Push(unsigned int attrib_count, unsigned int position_count) {
		return;
	}
	template<>
	void Push<float>(unsigned int attrib_count, unsigned int position_count) {
		m_Elements.push_back({ GL_FLOAT, attrib_count, position_count, false });
		m_Stride += sizeof(GL_FLOAT);
	}
	inline const std::vector<VertexBufferElement> GetElements() { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; };
};