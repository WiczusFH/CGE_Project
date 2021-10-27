#include "ship.h"
#include <iostream>
#include <list>
#include <thread>
#include <chrono>
const char* SHIP_PATH = "textures/spaceship.png";


Ship::Ship(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout, std::list<Laser>& laserList, unsigned int objIndex)
	:shader(shader), renderer(renderer), vertexBufferLayout(vertexBufferLayout), objIndex(objIndex), laserList(laserList)
{
	collisionBox.Y.size = 0.08f;
	collisionBox.X.size = 0.2f;
	vertexArray = new VertexArray();
	vertexBuffer = new VertexBuffer(VertexData, sizeof(VertexData));
	indexBuffer = new IndexBuffer(Indices, sizeof(Indices) / sizeof(unsigned int));
	texture = new Texture(SHIP_PATH);
	vertexArray->AddBuffer(*vertexBuffer, vertexBufferLayout); 
	vertexBuffer->updateVertexBuffer(VertexData, sizeof(VertexData)); //-M
	texture->Bind();
	shader.SetUniform1i("u_Texture", 0);

}

void Ship::updateVertexData()
{
	VertexData[0] = collisionBox.X.position + collisionBox.X.size;
	VertexData[1] = collisionBox.Y.position + collisionBox.Y.size;
	VertexData[4] = collisionBox.X.position - collisionBox.X.size;
	VertexData[5] = collisionBox.Y.position + collisionBox.Y.size;
	VertexData[8] = collisionBox.X.position - collisionBox.X.size;
	VertexData[9] = collisionBox.Y.position - collisionBox.Y.size;
	VertexData[12] = collisionBox.X.position + collisionBox.X.size;
	VertexData[13] = collisionBox.Y.position - collisionBox.Y.size;
}


void Ship::movement(float cameraPosX) {
	switch (DirectionActive[0])
	{
	case 0:
		break;
	case -1:
		moveLeft();
		break;
	case 1:
		moveRight();
		break;
	default:
		break;
	}
	switch (DirectionActive[1])
	{
	case 0:
		break;
	case -1:
		moveDown();
		break;
	case 1:
		moveUp();
		break;
	default:
		break;
	}
	if (cameraPosX >= collisionBox.X.position) {
		collisionBox.X.position = cameraPosX;
	}
}
void Ship::loadNextShot() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1200));
	readyToShoot = true;
}
void Ship::shoot() {
	if (readyToShoot) {
		laserList.push_back(Laser(shader, renderer, vertexBufferLayout, collisionBox.X.position + 0.15f, collisionBox.Y.position, 3));
		readyToShoot = false;
	}
}

void Ship::sendToRenderer() {
	//movement(); //-R move to a different function, this should only be rendering
	updateVertexData();
	texture->Bind();
	vertexBuffer->Bind();
	vertexBuffer->updateVertexBuffer(VertexData, sizeof(VertexData));
	renderer.Draw(*vertexArray, *indexBuffer, shader);
	vertexBuffer->Unbind();
	texture->Unbind();
}
