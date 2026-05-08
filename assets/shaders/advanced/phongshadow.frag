#version 330 core
in vec2 fUV;
in vec3 fNormal;
in vec3 worldPos;

in vec4 lightSpaceClipCoord;

out vec4 FragColor;
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform float specularIntensity;
uniform float mShiness;
uniform sampler2D samplerAsuna;
uniform sampler2D specularMask;
uniform sampler2D shadowMapSampler; //
uniform vec3 cameraPosition;


float calculateShadow() {
    // 找到当前像素在光源空间下的NDC坐标
    vec3 lightNDC = lightSpaceClipCoord.xyz / lightSpaceClipCoord.w;
    // 找到当前像素在ShadowMap上的UV
    vec3 projCoord = lightNDC * 0.5 + 0.5;
    vec2 uv = projCoord.xy;
    // 使用UV对Shadow Map进行采样，得到ClosestDepth
    float cloestDepth = texture(shadowMapSampler, uv).r;
    // 对比当前像素在光源空间的深度值，与ClosestDepth比大小
    float selfDepth = projCoord.z;
    float shadow = selfDepth > cloestDepth ? 1.0f : 0.0;
    return shadow;
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
    float flagg = texture(specularMask, fUV).r;
    vec3 specular = lightColor * specularFactor * flag * specularIntensity * flagg;

    vec3 ambient = ambientColor * objectColor;
    vec3 finalColor = diffuse + specular;
    float shadow = calculateShadow();

    vec3 result = finalColor * (1 - shadow) + ambient;
    FragColor = vec4(result, 1.0f);
}