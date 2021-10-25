#pragma once

#include <GL/glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "shader.h"

class Renderer {
private:

public:
	void Draw(VertexArray& vertexArray, IndexBuffer& indexBuffer, Shader& shader);
};