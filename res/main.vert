#version 460 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 color;

uniform mat4 project;
uniform mat4 view;

out vec3 v_color;

void main() {
	v_color = color;
	gl_Position = project * view * vec4(pos, 0, 1);
}