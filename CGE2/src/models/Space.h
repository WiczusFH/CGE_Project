#pragma once
#include <vector>
#include "../Textures.h"
#include "../Shader.h"
#include <iostream>
#include "../Physics.h"

class Space {
private:
	float x = 50.0;
	float VertexData[16] = {
		0.0, 0.0, x, 1,
		0.0, 0.0, 0.0, 1,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, x, 0.0
	};
	unsigned int Indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	CollisionBox collisionBox;
	Texture* texture;
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	VertexArray* vertexArray;

	VertexBufferLayout& vertexBufferLayout;
	Renderer& renderer;
	Shader& shader;


public:
	Space(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout, float sizeX);
	void sendToRenderer();
};