#pragma once

class IndexBuffer {
private:
	unsigned int m_RendererId;
	unsigned int index_count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind();
	void Unbind();

	inline unsigned int GetCount() const{ return index_count; }
};