#version 330 core
out vec4 FragColor;
in vec2 fUV;

uniform sampler2D diffuse;
void main() {
    vec3 color = texture(diffuse, fUV).rgb;
    color = pow(color, vec3(1.0/2.2));
    FragColor = vec4(color, 1.0f);
}