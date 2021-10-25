#pragma once
#include <vector>
#include "../Textures.h"
#include "../Shader.h"
#include <iostream>
#include "../Physics.h"


class Asteroid {
private:
	float identityMatrix[16] = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 1.0
	};
	float rotation=0;
	float rotationSpeed = 0;
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
	float rotationMatrix[16] = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	float centrumMatrix[16] = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	};
	float centrumMatrixInverse[16] = {
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 1.0
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
	void updateAsteroid();
	void updateVertexData();
	Asteroid(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout, float posX, float posY, float size, int imageIndex, unsigned int objIndex);
	void sendToRenderer();
};