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
uniform float bias;
uniform vec3 cameraPosition;

#define NUM_SAMPLES 32
#define PI 3.141592653589793
#define PI2 6.283185307179586

float rand_2to1(vec2 uv) { // AI generate
    // 0 - 1
    const highp float a = 12.9898, b = 78.233, c = 43758.5453;
    highp float dt = dot( uv.xy, vec2( a,b ) ), sn = mod( dt, PI );
    return fract(sin(sn) * c);
}

uniform float diskTightness;
vec2 disk[NUM_SAMPLES];
void poissonDiskSamples(vec2 randomSeed) {
    // init angle
    float angle = rand_2to1(randomSeed) * PI2;

    // init radius
    float radius = 1.0 / float(NUM_SAMPLES);
    // angle step
    float angleStep = 3.883222077450933;

    // radius step
    float radiusStep = radius;

    // for loop
    for (int i = 0; i < NUM_SAMPLES; i++) {
        disk[i] = vec2(cos(angle), sin(angle)) * pow(radius, diskTightness);
        radius += radiusStep;
        angle += angleStep;
    }

}

float autoBias(vec3 normal, vec3 lightDirection) {
    vec3 normalN = normalize(normal);
    vec3 lightDir = normalize(lightDirection);
    return max(bias * (1 - dot(normalN, lightDir)), 0.0005);
}

uniform float pcfRadius;
float pcf(vec3 normal, vec3 lightDirection) {
    // 找到当前像素在光源空间下的NDC坐标
    vec3 lightNDC = lightSpaceClipCoord.xyz / lightSpaceClipCoord.w;
    // 找到当前像素在ShadowMap上的UV
    vec3 projCoord = lightNDC * 0.5 + 0.5;
    vec2 uv = projCoord.xy;
    if (projCoord.z > 1.0 || uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0) {
        return 0.0;
    }
    // 使用UV对Shadow Map进行采样，得到ClosestDepth
    float depth = projCoord.z;
    poissonDiskSamples(uv);
    vec2 texelSize = 1.0 / vec2(textureSize(shadowMapSampler, 0));
    float sum = 0.0f;
//    for (int x = -1; x <= 1; x++) {
//        for (int y = -1; y <= 1; y++) {
//            float cloestDepth = texture(shadowMapSampler, uv + vec2(x,y) * texelSize).r;
//            sum += cloestDepth < (depth - autoBias(normal, lightDirection)) ? 1.0 : 0.0;
//        }
//    }
    for (int i = 0; i < NUM_SAMPLES; i++) {
        float cloestDepth = texture(shadowMapSampler, uv + disk[i] * pcfRadius * texelSize).r;
        sum += cloestDepth < (depth - autoBias(normal, lightDirection)) ? 1.0 : 0.0;
    }
    return sum / float(NUM_SAMPLES);
}



float calculateShadow(vec3 normal, vec3 lightDirection) {
    // 找到当前像素在光源空间下的NDC坐标
    vec3 lightNDC = lightSpaceClipCoord.xyz / lightSpaceClipCoord.w;
    // 找到当前像素在ShadowMap上的UV
    vec3 projCoord = lightNDC * 0.5 + 0.5;
    vec2 uv = projCoord.xy;
    // 使用UV对Shadow Map进行采样，得到ClosestDepth
    float cloestDepth = texture(shadowMapSampler, uv).r;
    // 对比当前像素在光源空间的深度值，与ClosestDepth比大小
    float selfDepth = projCoord.z - autoBias(normal, lightDirection);
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
    float shadow = pcf(fNormal, -lightDirection);

    vec3 result = finalColor * (1 - shadow) + ambient;
    FragColor = vec4(result, 1.0f);
}
