#version 330 core
in vec2 fUV;
in vec3 fNormal;
in vec3 worldPos;
out vec4 FragColor;
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform sampler2D samplerAsuna;
uniform vec3 cameraPosition;
void main() {
    vec3 objectColor = texture(samplerAsuna, fUV).xyz;
    vec3 diffuse = lightColor * objectColor * clamp(dot(normalize(fNormal), -normalize(lightDirection)), 0, 1);

    vec3 viewDirection = worldPos - cameraPosition;
    vec3 specular = lightColor * objectColor * clamp(dot(normalize(reflect(lightDirection, fNormal)), -normalize(viewDirection)), 0, 1);
    vec3 result = diffuse + specular;
    FragColor = vec4(result, 1.0f);
}