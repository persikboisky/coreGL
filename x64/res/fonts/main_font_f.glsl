#version 460 core

in vec2 text_coord;
in vec4 v_color;

out vec4 f_color;

uniform sampler2D text;

void main()
{
	f_color = v_color * texture(text, text_coord);
}