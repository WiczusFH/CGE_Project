#pragma once
#include <vector>
#include "../Textures.h"
#include "../Shader.h"
#include <iostream>
#include "../Physics.h"



class Ship {
private:
	float speed = 0.04f;
	float VertexData[16] = {
		0.3, 0.3,  1.0, 1.0,
		-0.3, 0.3, 0.0, 1.0,
		- 0.3,-0.3, 0.0, 0.0,
		0.3, -0.3, 1.0, 0.0
	};
	unsigned int Indices[6]= {
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
	int DirectionActive[2] = {0,0};
	CollisionBox getCollisionBox() { return collisionBox; }

	Ship(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout, unsigned int objIndex);
	Ship(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout,float pos, unsigned int objIndex);
	void updateVertexData();
	void sendToRenderer();
	
	void movement(float cameraPosX=0);

	inline void moveUp() { collisionBox.Y.position += speed;  }
	inline void moveDown() { collisionBox.Y.position -= speed;}
	inline void moveLeft() { collisionBox.X.position -= speed;}
	inline void moveRight() { collisionBox.X.position += speed;}
};