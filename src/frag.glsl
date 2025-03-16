#version 460 core

out vec4 f_color;

in vec2 text_c;

//uniform vec3 color;
uniform sampler2D text;

void main() {
	f_color = vec4(1, 0, 0, 1); //* texture2D(text, text_c);
}