#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 v_pos;
out vec3 v_normal;

uniform vec3 u_position;
uniform mat4 view;
uniform mat4 proj;

void main() {
	vec4 pos = proj * view * vec4(u_position + position, 1.0);
	v_pos = pos.xyz;
	v_normal = normal;
	gl_Position = pos;
}