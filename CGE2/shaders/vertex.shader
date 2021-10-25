#version 330 core

layout(location = 0) in vec4 position;
layout(location  = 1) in vec2 texCoord;

out vec2 v_TexCoord;
uniform mat4 u_VIEW;
uniform mat4 u_PRO;
uniform mat4 u_ROT;
uniform mat4 u_CEN;
uniform mat4 u_CENI;
void main() { 
	gl_Position = u_PRO*u_VIEW*u_CENI*u_ROT*u_CEN*position;
	v_TexCoord = texCoord;
};
