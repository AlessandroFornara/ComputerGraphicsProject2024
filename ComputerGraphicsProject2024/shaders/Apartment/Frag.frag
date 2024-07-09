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
	vec3 eyePos;
	float angleDiff;
	float angleSpec;
}tubo;

vec3 diffuseWithToon(vec3 Norm, vec3 ViewDir, vec3 lightdir, vec3 color){
	float percentage;
	
	float cosAlpha = dot(Norm,lightdir);
	if(cosAlpha <= 0){
		percentage = 0;
	}else if(cosAlpha <= 0.1){
		percentage = 150 * cosAlpha;
	}else if(cosAlpha <= tubo.angleDiff){
		percentage = 15 +  850 * (0.1 - (tubo.angleDiff - cosAlpha));
	}else{
		percentage = 100;
	}
	
	return color * percentage / 100;
}

vec3 spectWithToon(vec3 Norm, vec3 ViewDir, vec3 lightdir, vec3 color){
	
	float percentage;
	vec3 r = -reflect(lightdir, Norm);
	float cosBeta = dot(r, ViewDir);
	if(cosBeta <=0.9){
		percentage = 0;
	}else if(cosBeta <= tubo.angleSpec){
		percentage = 100 * ( (1-tubo.angleSpec) - (tubo.angleSpec - cosBeta)) / (1-tubo.angleSpec);
	}else{  
		percentage = 100;
	}
	return (color * percentage / 100);
}

void main() {

	vec3 Albedo = texture(tex, fragUV).rgb;

	vec3 diffElement = diffuseWithToon( normalize(fragNorm), normalize(tubo.eyePos - fragPos), tubo.lightDir, Albedo);
	vec3 speElement = spectWithToon(normalize(fragNorm), normalize(tubo.eyePos - fragPos), tubo.lightDir, Albedo);
	vec3 col  =  (diffElement + speElement) * tubo.lightColor.xyz;
	
	outColor = vec4(col, 1.0f);
	
}