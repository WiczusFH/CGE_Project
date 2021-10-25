#include "Camera.h"

Camera::Camera(float aspectRatio)
{
	projectionMatrix[0] = aspectRatio;
}

void Camera::setProjection()
{
	for (auto shader = shaders.begin(); shader != shaders.end(); ++shader) {
		shader->SetUniformMat4f("u_PRO", projectionMatrix);
	}
}
void Camera::setView()
{
	for (auto shader = shaders.begin(); shader != shaders.end(); ++shader) {
		shader->SetUniformMat4f("u_VIEW", viewMatrix);
	}
}
void Camera::scrollX(float x)
{
	X += x;
	viewMatrix[3] = -X;
}
