#version 460 core

out vec4 f_color;

uniform vec4 background;

void main()
{
	f_color = background;
}