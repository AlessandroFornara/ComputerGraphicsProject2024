#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform sampler2D tex;

layout(set = 0, binding = 2) uniform spotLightUBO {
    vec3 lightDir[4];
    vec3 lightPos[4];
    vec3 lightColor[4];
    float cosIn;
    float cosOut;
    vec3 eyePos;
} subo;

vec3 spot_light_color(vec3 lightPos, vec3 pos, vec3 lightDir, vec3 lightColor) {
    vec3 L0 = lightColor * pow(3.0f / length(pos - lightPos), 2.0);
    float clampValue = clamp((dot(normalize(lightPos - pos), lightDir) - subo.cosOut) / (subo.cosIn - subo.cosOut), 0, 1);
    return L0 * clampValue;
}

vec3 lambertDiffuse(vec3 Norm, vec3 lightPos, vec3 Color, vec3 fragmentPosition) {
    vec3 direction = normalize(lightPos - fragmentPosition);
    vec3 diffuse = Color * clamp(dot(Norm, direction), 0, 1);
    return diffuse;
}

vec3 phongSpecular(vec3 Norm, vec3 lightPos, vec3 specularColor, vec3 eyeDir) {
    vec3 direction = normalize(lightPos - fragPos);
    vec3 f_specular = specularColor * pow(clamp(dot(eyeDir, -reflect(direction, Norm)), 0, 1), 80.0f);
    return f_specular;
}

void main() {
    vec3 norm = normalize(fragNorm);
    vec3 EyeDir = normalize(subo.eyePos - fragPos);
    
    vec3 Albedo = texture(tex, fragUV).rgb;
    vec3 specularColor = vec3(1.0f, 1.0f, 1.0f);
    
    vec3 diffSpot[4];
    vec3 spec[4];
    vec3 spotColor[4];
    vec3 finalResult = vec3(0.0f);

    for (int i = 0; i < 4; ++i) {
        diffSpot[i] = lambertDiffuse(norm, subo.lightPos[i], Albedo, fragPos);
        spec[i] = phongSpecular(norm, subo.lightPos[i], specularColor, EyeDir);
        spotColor[i] = spot_light_color(subo.lightPos[i], fragPos, subo.lightDir[i], subo.lightColor[i]);
        finalResult += (diffSpot[i] + spec[i]) * spotColor[i];
    }

    outColor = vec4(finalResult, 1.0f); 
}
