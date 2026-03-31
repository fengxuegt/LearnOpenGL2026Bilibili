#version 330 core
out vec4 FragColor;
in vec3 fUV;
uniform sampler2D diffuse;

const float PI = 3.1415926535897932384626433832795;

vec2 uvwToUv(vec3 uvwN){
    float phi = asin(uvwN.y);
    float theta = atan(uvwN.z, uvwN.x);
    float u = theta / (2.0 * PI) + 0.5;
    float v = phi / PI + 0.5;
    return vec2(u, v);
}

void main() {
    vec3 uvwN = normalize(fUV);
    vec2 uv = uvwToUv(uvwN);
    FragColor = vec4(texture(diffuse, uv).rgb, 1.0f);
}