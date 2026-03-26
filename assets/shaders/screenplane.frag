#version 330 core
out vec4 FragColor;
in vec2 fUV;

uniform sampler2D diffuse;
void main() {
    FragColor = vec4(texture(diffuse, fUV).rgb, 1.0f);
}