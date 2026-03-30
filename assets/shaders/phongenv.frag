#version 330 core
in vec2 fUV;
in vec3 fNormal;
in vec3 worldPos;
out vec4 FragColor;
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform float specularIntensity;
uniform float mShiness;
uniform sampler2D samplerAsuna;
uniform vec3 cameraPosition;

uniform samplerCube cubeSampler;

vec3 calculateAmbientenv(vec3 viewDir, vec3 normal) {
    vec3 reflectionN = normalize(reflect(viewDir, normal));
    return texture(cubeSampler, reflectionN).rgb;
}

void main() {
    vec3 objectColor = texture(samplerAsuna, fUV).xyz;
    vec3 diffuse = lightColor * objectColor * clamp(dot(normalize(fNormal), -normalize(lightDirection)), 0, 1);
    vec3 lightDirectionN = normalize(lightDirection);
    vec3 normalN = normalize(fNormal);
    float flag = step(0.0f, dot(-lightDirectionN, normalN));

    vec3 viewDirection = normalize(worldPos - cameraPosition);
    vec3 lightReflect = normalize(reflect(lightDirectionN, normalN));
    float specularFactor = clamp(dot(lightReflect, -viewDirection), 0, 1);
    specularFactor = pow(specularFactor, mShiness);
    vec3 specular = lightColor * specularFactor * flag * specularIntensity;

//    vec3 ambient = ambientColor * objectColor;
    vec3 ambient = calculateAmbientenv(viewDirection, normalN) * objectColor;

    vec3 result = diffuse + specular + ambient;
    FragColor = vec4(result, 1.0f);
}