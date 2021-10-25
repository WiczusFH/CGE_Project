#include "Laser.h"

const char* LASER_PATH = "textures/laser.png";


Laser::Laser(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout,float positionX, float positionY, unsigned int objIndex)
	:shader(shader), renderer(renderer), vertexBufferLayout(vertexBufferLayout), objIndex(objIndex)
{
	collisionBox.Y.size = 0.025f;
	collisionBox.X.size = 0.2f;
	collisionBox.Y.position = positionY;
	collisionBox.X.position = positionX;
	vertexArray = new VertexArray();
	vertexBuffer = new VertexBuffer(VertexData, sizeof(VertexData));
	indexBuffer = new IndexBuffer(Indices, sizeof(Indices) / sizeof(unsigned int));
	texture = new Texture(LASER_PATH);
	vertexArray->AddBuffer(*vertexBuffer, vertexBufferLayout);
	vertexBuffer->updateVertexBuffer(VertexData, sizeof(VertexData)); //-M
	texture->Bind();
	shader.SetUniform1i("u_Texture", 0);

}

void Laser::updateVertexData()
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


void Laser::movement() {
	collisionBox.X.position += speed;
}

void Laser::sendToRenderer() {
	updateVertexData();
	texture->Bind();
	vertexBuffer->Bind();
	vertexBuffer->updateVertexBuffer(VertexData, sizeof(VertexData));
	renderer.Draw(*vertexArray, *indexBuffer, shader);
	vertexBuffer->Unbind();
	texture->Unbind();
}