#version 410 core

layout(location = 0) in vec3 a_vertex3f;
layout(location = 1) in vec3 a_normal3f;
layout(location = 2) in vec3 a_tangent3f;
layout(location = 3) in vec3 a_texCoord3f;

uniform mat4 u_mvpMatrix_4x4f;

out vec3 o_texCoord3f;
out vec3 o_vertex3f;

void main() {
    o_texCoord3f = a_texCoord3f;
    o_vertex3f = a_vertex3f;
    gl_Position = u_mvpMatrix_4x4f * vec4(a_vertex3f, 1.0);
}
