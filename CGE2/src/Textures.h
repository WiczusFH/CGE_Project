#pragma once
#include "renderer.h"

class Texture {
private:
	unsigned int id;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_Depth;
public:
	Texture(const std::string& path, unsigned int mode=0);
	~Texture();

	void Bind(unsigned int slot=0);
	void Unbind();

	inline int getWidth() { return m_Width; }
	inline int getHeight() { return m_Height; }
	inline int getDepth() { return m_Depth; }
};