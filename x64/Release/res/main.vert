#version 460 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 col;

uniform mat4 matrixView;
uniform mat4 matrixProject;

out vec4 v_color;

void main() {
    v_color = vec4(col, 1);
    gl_Position = matrixProject * matrixView * vec4(pos, 0, 1);
}