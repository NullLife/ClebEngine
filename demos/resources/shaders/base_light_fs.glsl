#version 410 core

in vec3 o_world_vertex3f;
in vec3 o_world_normal3f;

in vec3 o_texCoord3f;


struct Light {
    int type;
    vec4 diffuse_color;
    vec4 specular_color;
    
    vec3 position;
    vec3 direction;
    float cutoff;
    vec4 attenuation;
};
struct Material {
    float diffuse_intensity;
    float specular_intensity;
    float shininess;
};

uniform sampler2D u_diffuseTex_1i;

uniform vec3 u_camera_position;
uniform vec4 u_ambient_color;

uniform Light u_light;
uniform Material u_mtl;

out vec4 color;

//==================================//

vec4 calcPointLight(Light light, vec3 vp, vec3 vn) {
    vec3 dir = light.position - vp;
    
    float dist = length(dir);
    dir = dir / dist;
    
    float atten = 1.0 / (light.attenuation.x + light.attenuation.y * dist + light.attenuation.z * dist * dist);
    
    float diff = max(dot(vn, dir), 0.0);
    vec4 diffuseLight = u_mtl.diffuse_intensity * diff * light.diffuse_color * atten;
    
    vec3 camDir = normalize(u_camera_position - vp);
    
    vec3 halfVector = normalize(dir + camDir);
    //vec3 reflectDirection = reflect(-dir, vn);
    float spec = pow(max(dot(vn, halfVector), 0.0), u_mtl.shininess);
    vec4 specularLight = u_mtl.specular_intensity * spec * light.specular_color * atten;
    
    return min(diffuseLight + specularLight), vec4(1.0));
}


void main() {
    vec4 texColor = texture(defaultSampler, vVertex.texCoord); = texture(u_diffuseTex_1i, o_texCoord3f.xy);
    
    vec4 lightsColor = u_ambient_color;
    if (u_light.type == 0) { // Directional light.
        
    } else if (u_light.type == 1) { // Point light.
        lightsColor += calcPointLight(u_light, o_world_vertex3f, o_world_normal3f);
    } else { // Spot light.
        
    }
    color = texColor * min(lightsColor, vec4(1.0f));
}
