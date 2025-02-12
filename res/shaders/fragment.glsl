#version 460 core

in vec3 v_color;
out vec4 f_color;

vec4 color = vec4(v_color, 1);

void main() {
	f_color = color;
}