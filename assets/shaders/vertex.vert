#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aUV;
out vec3 vColor;
out vec2 fUV;

uniform mat4 transMat;
uniform mat4 viewMat;
void main() {
    gl_Position = viewMat * transMat * vec4(aPos, 1.0f);
    vColor = aColor;
    fUV = aUV;
}