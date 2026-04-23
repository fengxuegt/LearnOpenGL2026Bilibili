#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec2 aUV;
layout(location = 1) in vec3 aNormal;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 biTangent;
out vec2 fUV;
out vec3 fNormal;
out vec3 worldPos;
out mat3 tbn;

uniform mat4 transMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;
uniform mat4 normalMat;
void main() {
    gl_Position = projectionMat * viewMat * transMat * vec4(aPos, 1.0f);
    fUV = aUV;
    fNormal = mat3(normalMat) * aNormal;
    worldPos = (transMat * vec4(aPos, 1.0f)).xyz;

    vec3 tangent = normalize(mat3(transMat) * aTangent);
//    tangent = normalize(tangent - dot(tangent, fNormal) * fNormal); // 施密特正交化
    vec3 bitangent = normalize(mat3(transMat) * biTangent);

    tbn = mat3(tangent, bitangent, fNormal);

}