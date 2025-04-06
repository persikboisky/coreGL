#version 460 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 text_c;
layout (location = 2) in vec4 l_color;

out vec2 text_coord;
out vec4 v_color;

uniform mat4 matrix;

void main()
{
	v_color = l_color;
	text_coord = text_c;
	gl_Position = matrix * vec4(pos, -1.0f, 1.0f);
}