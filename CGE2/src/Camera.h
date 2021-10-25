#pragma once
#include "shader.h"
#include <list>

class Camera {
private:
	std::list<Shader> shaders;
	float X=0;
	float Y=0;
	float viewMatrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,0,0,
		0,0,0,1
	};
	float projectionMatrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,0,0,
		0,0,0,1
	};
public:
	Camera(float aspectRatio);
	void addShader(Shader shader) { shaders.push_back(shader); }
	void setProjection();
	void setView();
	float getX() { return X; }
	void scrollX(float x);
};