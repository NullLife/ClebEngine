#version 410 core

layout(location = 0) in vec3 a_vertex3f;

uniform mat4 u_mvpMatrix_4x4f;

void main() {
    gl_Position = u_mvpMatrix_4x4f * vec4(a_vertex3f, 1.0);
}
