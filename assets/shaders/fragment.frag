#version 330 core
in vec3 vColor;
in vec2 fUV;
out vec4 FragColor;
uniform float time;
uniform sampler2D samplerAsuna;
void main() {
//    FragColor = vec4(vColor, 1.0f) * time;
//    vec3 color = texture(samplerAsuna,fUV);
    FragColor = texture(samplerAsuna, fUV);
}