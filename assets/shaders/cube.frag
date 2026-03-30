#version 330 core
out vec4 FragColor;
in vec3 fUV;
uniform samplerCube diffuse;
void main() {
    FragColor = vec4(texture(diffuse, fUV).rgb, 1.0f);
}