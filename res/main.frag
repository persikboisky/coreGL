#version 460 core

out vec4 f_color;
in vec3 v_color;

void main() {
    f_color = vec4(v_color, 1);
}