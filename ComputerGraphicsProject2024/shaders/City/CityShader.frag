#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

// This defines the color computed by this shader. Generally is always location 0.
layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform BlinnUniformBufferObject {
	float Pow;
	vec3 lightDir;
	vec4 lightColor;
	vec3 eyePos;
} gubo;


layout(set = 1, binding = 1) uniform sampler2D tex;

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos - fragPos);
	
	vec3 lightDir = normalize(gubo.lightDir);
	vec3 lightColor = gubo.lightColor.rgb;

	vec3 Diffuse = texture(tex, fragUV).rgb * 0.975 * max(dot(Norm, lightDir),0.0);
	vec3 Specular = vec3(pow(max(dot(Norm, normalize(lightDir + EyeDir)),0.0), gubo.Pow));
	vec3 Ambient = texture(tex, fragUV).rgb * 0.15f;
	
	vec3 col  = (Diffuse + Specular) * lightColor + Ambient;
	
	outColor = vec4(col, 1.0f);
}