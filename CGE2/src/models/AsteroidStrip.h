#pragma once
#include <vector>
#include "../Textures.h"
#include "../Shader.h"
#include <iostream>
#include "../Physics.h"
class AsteroidStrip {
private:
	float speed = 0.08f;
	float x = 100.0;
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
	unsigned int objIndex;
	CollisionBox getCollisionBox() { return collisionBox; }

	AsteroidStrip(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout, float posY, float sizeY,float sizeX, float offset,unsigned int objIndex);
	void sendToRenderer();
};