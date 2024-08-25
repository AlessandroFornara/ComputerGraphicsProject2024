#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

layout(set = 1, binding = 1) uniform sampler2D tex;

layout(set = 0, binding = 0) uniform ToonUniformBufferObject {
	vec3 lightDir;
	vec3 lightColor;
	vec3 lightPos;
	vec3 eyePos;
	vec3 diffSpecJolly;
}tubo;

vec3 diffuse(vec3 Norm, vec3 lightPos, vec3 Color, vec3 fragmentPosition) {
    vec3 direction = normalize(lightPos - fragmentPosition);
    vec3 diffuse = Color * clamp(dot(Norm, direction), 0, 1);
    return diffuse;
}



void main() {
	vec3 Albedo = texture(tex, fragUV).rgb;
	vec3 Norm = normalize(fragNorm);
	
	vec3 diff = diffuse(Norm, tubo.lightpos ,tubo.lightColor, fragPos);
	
	outColor = vec4(Albedo * diff, 1.0f);	
}