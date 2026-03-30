#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 aUV;
layout(location = 1) in vec3 aNormal;

out vec3 fUV;
uniform mat4 transMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;
void main() {
    gl_Position = projectionMat * viewMat * transMat * vec4(aPos, 1.0f);
    gl_Position = gl_Position.xyww;
    fUV = aPos;
}