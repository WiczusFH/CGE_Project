#include "Textures.h"
#include "../Libs/stb_image.h"

Texture::Texture(const std::string& path, unsigned int mode)
	: id(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0),m_Depth(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(),&m_Width, &m_Height, &m_Depth, 4);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	if (mode == 0) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	if (mode == 1) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA,  GL_UNSIGNED_BYTE, m_LocalBuffer);
	Unbind();

	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}
}
Texture::~Texture()
{
	glDeleteTextures(1, &id);
}
void Texture::Bind(unsigned int slot) {
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}
