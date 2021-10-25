#include "Win.h"

const char* WIN_PATH = "textures/win.png";

WinScreen::WinScreen(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout, float size)
	:shader(shader), renderer(renderer), vertexBufferLayout(vertexBufferLayout)
{
	collisionBox.Y.size = size;
	collisionBox.X.size = size*2;
	collisionBox.Y.position = 0;
	collisionBox.X.position = 0;


	updateVertexData();
	vertexArray = new VertexArray();
	vertexBuffer = new VertexBuffer(VertexData, sizeof(VertexData));
	indexBuffer = new IndexBuffer(Indices, sizeof(Indices) / sizeof(unsigned int));
	texture = new Texture(WIN_PATH, 0);
	vertexArray->AddBuffer(*vertexBuffer, vertexBufferLayout);
	vertexBuffer->updateVertexBuffer(VertexData, sizeof(VertexData)); //-M
	texture->Bind();
	shader.SetUniform1i("u_Texture", 0);

}
void WinScreen::updateVertexData() {
	VertexData[0] = collisionBox.X.position + collisionBox.X.size;
	VertexData[1] = collisionBox.Y.position + collisionBox.Y.size;
	VertexData[4] = collisionBox.X.position - collisionBox.X.size;
	VertexData[5] = collisionBox.Y.position + collisionBox.Y.size;
	VertexData[8] = collisionBox.X.position - collisionBox.X.size;
	VertexData[9] = collisionBox.Y.position - collisionBox.Y.size;
	VertexData[12] = collisionBox.X.position + collisionBox.X.size;
	VertexData[13] = collisionBox.Y.position - collisionBox.Y.size;
}

void WinScreen::updateX(float x) {
	collisionBox.X.position = x;
	updateVertexData();
}
void WinScreen::sendToRenderer()
{
	texture->Bind();
	vertexBuffer->Bind();
	vertexBuffer->updateVertexBuffer(VertexData, sizeof(VertexData));
	renderer.Draw(*vertexArray, *indexBuffer, shader);
	vertexBuffer->Unbind();
	texture->Unbind();
}