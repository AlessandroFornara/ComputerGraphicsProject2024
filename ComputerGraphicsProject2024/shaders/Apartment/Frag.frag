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
	vec3 lightpos;
	vec3 eyePos;
	vec3 diffSpecJolly;
}tubo;

vec3 diffuseWithToon(vec3 Norm, vec3 lightdir, vec3 color){
	float percentage;
	
	float cosAlpha = dot(tubo.lightDir, Norm);
	
	if(cosAlpha == 0.0){
		percentage = 0.5;
	}else if(cosAlpha == 1.0){
		percentage = 0.2;
	}else if(cosAlpha == -1.0){
		percentage = 0.8;
	}
		
	return color * percentage;
}

vec3 spectPhon(vec3 Norm, vec3 eyeDir, vec3 color){
	if(Norm.y == 1.0f){
		vec3 direction = normalize(tubo.lightpos - fragPos);
		vec3 f_specular = color * pow(clamp(dot(eyeDir, -reflect(direction, Norm)), 0, 1), 10.0f);
		return color * f_specular;
	}
	return vec3(0.0, 0.0, 0.0);
}

void main() {
	vec3 Albedo = texture(tex, fragUV).rgb;
	vec3 Norm = normalize(fragNorm);
	vec3 diffElement = diffuseWithToon( normalize(fragNorm), tubo.lightDir , Albedo);
	vec3 speElement = spectPhon(normalize(fragNorm), normalize(tubo.eyePos - fragPos), vec3(0.6, 0.6, 0.6));
	vec3 col  =  (diffElement+speElement) * tubo.lightColor.xyz;
	outColor = vec4(col, 1.0f);	
}