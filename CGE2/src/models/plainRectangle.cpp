#include "plainRectangle.h"

#include "ship.h"
#include <iostream>

const char* PLAIN_RECTANGLE_PATH = "textures/plainrectangle.png";

PlainRectangle::PlainRectangle(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout)
	:shader(shader), renderer(renderer), vertexBufferLayout(vertexBufferLayout)
{

	vertexArray = new VertexArray();
	vertexBuffer = new VertexBuffer(VertexData, sizeof(VertexData));
	indexBuffer = new IndexBuffer(Indices, sizeof(Indices) / sizeof(unsigned int));
	texture = new Texture(PLAIN_RECTANGLE_PATH);

	vertexArray->AddBuffer(*vertexBuffer, vertexBufferLayout);
	vertexBuffer->updateVertexBuffer(VertexData, sizeof(VertexData)); //-M
	//shader.SetUniform4f("u_Color", 1.0, 0.0, 0.5, 1.0);
	texture->Bind();
	shader.SetUniform1i("u_Texture", 0);
}

PlainRectangle::PlainRectangle(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout, float pos)
	:shader(shader), renderer(renderer), vertexBufferLayout(vertexBufferLayout)
{
	position[0] = pos;
	position[1] = pos;

	vertexArray = new VertexArray();
	vertexBuffer = new VertexBuffer(VertexData, sizeof(VertexData));
	indexBuffer = new IndexBuffer(Indices, sizeof(Indices) / sizeof(unsigned int));
	texture = new Texture(PLAIN_RECTANGLE_PATH);

	vertexArray->AddBuffer(*vertexBuffer, vertexBufferLayout);
	vertexBuffer->updateVertexBuffer(VertexData, sizeof(VertexData)); //-M
	//shader.SetUniform4f("u_Color", 1.0,0.0,0.5,1.0);
	texture->Bind();
	shader.SetUniform1i("u_Texture", 0);
} // -R

PlainRectangle::~PlainRectangle()
{
}

void PlainRectangle::updateVertexData()
{
	VertexData[0] = position[0] + size;
	VertexData[1] = position[1] + size;
	VertexData[4] = position[0] - size;
	VertexData[5] = position[1] + size;
	VertexData[8] = position[0] - size;
	VertexData[9] = position[1] - size;
	VertexData[12] = position[0] + size;
	VertexData[13] = position[1] - size;
}

void PlainRectangle::sendToRenderer() {
	updateVertexData();

	texture->Bind();
	vertexBuffer->Bind();
	//shader.Bind();
	vertexBuffer->updateVertexBuffer(VertexData, sizeof(VertexData));
	renderer.Draw(*vertexArray, *indexBuffer, shader);
	//shader.Unbind();
	vertexBuffer->Unbind();
	texture->Unbind();
}