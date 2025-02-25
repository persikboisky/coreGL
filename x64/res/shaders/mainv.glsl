#version 460 core

layout (location = 0) in vec3 pos;

uniform vec3 position;
uniform mat4 view;
uniform mat4 proj;

void main() {
	vec3 coord_vert = position + pos;
	gl_Position = proj * view * vec4(coord_vert, 1.0);
}