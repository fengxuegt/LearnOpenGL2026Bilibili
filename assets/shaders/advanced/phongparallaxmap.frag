#version 330 core
in vec2 fUV;
in vec3 fNormal;
in vec3 worldPos;
in mat3 tbn;
out vec4 FragColor;
uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform float specularIntensity;
uniform float mShiness;
uniform sampler2D samplerAsuna;
uniform sampler2D normalMapSampler;
uniform sampler2D parallaxMapSampler;
uniform vec3 cameraPosition;
uniform float heightScale;

vec2 parallaxUV(vec2 uv, vec3 viewDir) {
    viewDir = normalize(transpose(tbn) * viewDir);
    float height = texture(parallaxMapSampler, uv).r;
    vec2 offset = viewDir.xy / viewDir.z * height * heightScale;
    return uv - offset;
}
vec2 parallaxUVSteep(vec2 uv, vec3 viewDir) {
    viewDir = normalize(transpose(tbn) * viewDir);
    // 准备基础数据
    float layerNum = 10.0f;
    float layerDepth = 1.0f / layerNum;
    vec2 deltaUV = viewDir.xy / viewDir.z * heightScale / layerNum;
    vec2 currentUV = uv;
    float currentSampleValue = texture(parallaxMapSampler, currentUV).r;
    float currentLayerDepth = 0.0f;
    // 循环步进
    while (currentLayerDepth < currentSampleValue) {
        currentUV -= deltaUV;
        currentSampleValue = texture(parallaxMapSampler, currentUV).r;
        currentLayerDepth += layerDepth;
    }

    // 已经是跳出循环了
    vec2 lastUV = currentUV + deltaUV;
    // 计算lastLen
    float lastLayerDepth = currentLayerDepth - layerDepth;
    float lastHeight = texture(parallaxMapSampler, lastUV).r;
    float lastLen = lastHeight - lastLayerDepth;

    // 计算current Len
    float currentLen = currentLayerDepth - currentSampleValue;
    float lastWeight = currentLen / (currentLen + lastLen);
    vec2 targetUV = mix(currentUV, lastUV, lastWeight);

    return targetUV;
}

void main() {
    vec3 viewDirection = normalize(worldPos - cameraPosition);
    vec2 realUV = parallaxUVSteep(fUV, viewDirection);

    //    vec3 normalN = normalize(fNormal);
    vec3 normalN = texture(normalMapSampler, realUV).rgb;
    normalN = normalN * 2.0 - vec3(1.0);
    normalN = normalize(tbn * normalN);
    vec3 objectColor = texture(samplerAsuna, realUV).xyz;
    vec3 diffuse = lightColor * objectColor * clamp(dot(normalize(normalN), -normalize(lightDirection)), 0, 1);
    vec3 lightDirectionN = normalize(lightDirection);

    float flag = step(0.0f, dot(-lightDirectionN, normalN));


    vec3 lightReflect = normalize(reflect(lightDirectionN, normalN));
    float specularFactor = clamp(dot(lightReflect, -viewDirection), 0, 1);
    specularFactor = pow(specularFactor, mShiness);
    vec3 specular = lightColor * specularFactor * flag * specularIntensity;

    vec3 ambient = ambientColor * objectColor;
    vec3 result = diffuse + specular + ambient;
    FragColor = vec4(result, 1.0f);
}