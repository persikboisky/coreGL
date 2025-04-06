#version 460 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec4 color;

out vec4 v_color;

void main()
{
	v_color = color;
	gl_Position = vec4(pos, 0.0, 1.0);
}