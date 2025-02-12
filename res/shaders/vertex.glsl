#version 460 core

layout (location = 0) in vec3 pos;

uniform mat4 proj;
uniform mat4 view;
uniform vec3 color;
uniform vec3 cord;

out vec3 v_color;

void main() {

	vec3 c = pos;
	c += cord;
	v_color = color;
	gl_Position = proj * view * vec4(c, 1.0);
}