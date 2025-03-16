#version 460 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 text_coord;

out vec2 text_c;

void main() {
	text_c = text_coord;
	gl_Position = vec4(pos, 0, 1);
}