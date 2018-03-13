#version 410 core

in vec3 o_texCoord3f;
in vec3 o_vertex3f;

uniform sampler2D u_diffuseTex_1i;

out vec4 color;

void main() {
    color = texture(u_diffuseTex_1i, o_texCoord3f.xy);
}
