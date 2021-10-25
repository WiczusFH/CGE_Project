#pragma once
#include <vector>
#include "../Textures.h"
#include "../Shader.h"
#include <iostream>

class PlainRectangle {
private:
	float position[2] = { 0,0 };
	float size = 0.3f;
	float VertexData[16] = {
		0.3, 0.3,  1.0, 1.0,
		-0.3, 0.3, 0.0, 1.0,
		-0.3,-0.3, 0.0, 0.0,
		0.3, -0.3, 1.0, 0.0
	};
	unsigned int Indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	VertexArray* vertexArray;
	Texture* texture;

	VertexBufferLayout& vertexBufferLayout;
	Renderer& renderer;
	Shader& shader;


public:
	int DirectionActive[2] = { 0,0 };

	PlainRectangle(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout);
	PlainRectangle(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout, float pos);
	~PlainRectangle();
	void updateVertexData();
	void sendToRenderer();
};