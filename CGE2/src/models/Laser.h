#pragma once
#include <vector>
#include "../Textures.h"
#include "../Shader.h"
#include <iostream>
#include "../Physics.h"



class Laser {
private:
	float speed = 0.035f;
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
	int DirectionActive[2] = { 0,0 };
	CollisionBox getCollisionBox() { return collisionBox; }

	Laser(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout, float positionX, float positionY, unsigned int objIndex);
	void updateVertexData();
	void sendToRenderer();

	void movement();
};