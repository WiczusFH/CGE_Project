#include "Asteroid.h"
#include <cmath>
const char* ASTEROID0_PATH = "textures/asteroid0.png";
const char* ASTEROID1_PATH = "textures/asteroid1.png";
const char* ASTEROID2_PATH = "textures/asteroid2.png";

Asteroid::Asteroid(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout, 
	float posX, float posY, float size, int imageIndex, unsigned int objIndex)
	:shader(shader), renderer(renderer), vertexBufferLayout(vertexBufferLayout), objIndex(objIndex)
{
	collisionBox.Y.size = size;
	collisionBox.X.size = size;
	collisionBox.Y.position = posY;
	collisionBox.X.position = posX;
	//rotation = rand() % 100-50;
	rotationSpeed = ((float)(rand() % 100) - 50)/800 ;
	VertexData[0] = collisionBox.X.position + collisionBox.X.size;
	VertexData[1] = collisionBox.Y.position + collisionBox.Y.size;
	VertexData[4] = collisionBox.X.position - collisionBox.X.size;
	VertexData[5] = collisionBox.Y.position + collisionBox.Y.size;
	VertexData[8] = collisionBox.X.position - collisionBox.X.size;
	VertexData[9] = collisionBox.Y.position - collisionBox.Y.size;
	VertexData[12] = collisionBox.X.position + collisionBox.X.size;
	VertexData[13] = collisionBox.Y.position - collisionBox.Y.size;
	vertexArray = new VertexArray();
	vertexBuffer = new VertexBuffer(VertexData, sizeof(VertexData));
	indexBuffer = new IndexBuffer(Indices, sizeof(Indices) / sizeof(unsigned int));
	if (imageIndex == 0) { texture = new Texture(ASTEROID0_PATH, 0); };
	if (imageIndex == 1) { texture = new Texture(ASTEROID1_PATH, 0); };
	if (imageIndex == 2) { texture = new Texture(ASTEROID2_PATH, 0); };
	vertexArray->AddBuffer(*vertexBuffer, vertexBufferLayout);
	vertexBuffer->updateVertexBuffer(VertexData, sizeof(VertexData)); //-M
	texture->Bind();
	shader.SetUniform1i("u_Texture", 0);
	centrumMatrix[3] = -collisionBox.X.position;
	centrumMatrix[7] = -collisionBox.Y.position;
	centrumMatrixInverse[3] = collisionBox.X.position;
	centrumMatrixInverse[7] = collisionBox.Y.position;
}
void Asteroid::updateAsteroid() {
	rotation += rotationSpeed;
}

void Asteroid::sendToRenderer()
{
	//createRotationMatrix
	rotationMatrix[0] = cos(rotation);
	rotationMatrix[1] = -sin(rotation);
	rotationMatrix[4] = sin(rotation);
	rotationMatrix[5] = cos(rotation);

	//shader.Bind();
	shader.SetUniformMat4f("u_ROT", rotationMatrix);
	shader.SetUniformMat4f("u_CEN", centrumMatrix);
	shader.SetUniformMat4f("u_CENI", centrumMatrixInverse);

	texture->Bind();
	vertexBuffer->Bind();
	vertexBuffer->updateVertexBuffer(VertexData, sizeof(VertexData));
	renderer.Draw(*vertexArray, *indexBuffer, shader);
	vertexBuffer->Unbind();
	texture->Unbind();
}
