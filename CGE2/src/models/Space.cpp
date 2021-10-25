#include "Space.h"


const char* SPACE_PATH = "textures/space.png";

Space::Space(Shader& shader, Renderer& renderer, VertexBufferLayout& vertexBufferLayout, float sizeX)
	:shader(shader), renderer(renderer), vertexBufferLayout(vertexBufferLayout)
{
	collisionBox.Y.size = 1;
	collisionBox.X.size = sizeX;
	collisionBox.Y.position = 0;
	collisionBox.X.position = 0;


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
	texture = new Texture(SPACE_PATH, 1);
	
	vertexArray->AddBuffer(*vertexBuffer, vertexBufferLayout);
	vertexBuffer->updateVertexBuffer(VertexData, sizeof(VertexData)); //-M
	texture->Bind();
	shader.SetUniform1i("u_Texture", 0);

}

void Space::sendToRenderer()
{
	texture->Bind();
	vertexBuffer->Bind();
	vertexBuffer->updateVertexBuffer(VertexData, sizeof(VertexData));
	renderer.Draw(*vertexArray, *indexBuffer, shader);
	vertexBuffer->Unbind();
	texture->Unbind();
}
