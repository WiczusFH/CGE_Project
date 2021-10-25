#pragma once
#include <vector>
#include "../Textures.h"
#include "../Shader.h"
#include <iostream>
#include "../Physics.h"

class Thruster {
private:
	float VertexData[16] = {
		0.0, 0.0, 1, 1,
		0.0, 0.0, 0.0, 1,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 1, 0.0
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
	Thruster(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout, float sizeX);
	void sendToRenderer();
};