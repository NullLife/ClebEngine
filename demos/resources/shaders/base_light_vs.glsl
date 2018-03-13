#version 410 core

layout(location = 0) in vec3 a_vertex3f;
layout(location = 1) in vec3 a_normal3f;
layout(location = 2) in vec3 a_tangent3f;
layout(location = 3) in vec3 a_texCoord3f;

uniform mat4 u_modelMatrix_4x4f;
uniform mat4 u_viewMatrix_4x4f;
uniform mat4 u_projectionMatrix_4x4f;


out vec3 o_world_vertex3f;
out vec3 o_world_normal3f;

out vec3 o_texCoord3f;

void main() {
    o_texCoord3f = a_texCoord3f;
    
    vec4 wv = u_modelMatrix_4x4f * vec4(a_vertex3f, 1.0);
    o_world_vertex3f = wv.xyz;
    o_world_normal3f = mat3(transpose(inverse(u_modelMatrix_4x4f))) * a_normal3f;
    
    gl_Position = u_projectionMatrix_4x4f * u_viewMatrix_4x4f * wv;
}
