#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;


layout(set = 0, binding = 0) uniform ApartmentLightBuffer {
    vec3 lightPos;
    vec3 lightColor;
	vec3 eyePos;
    vec3 rff;
} subo;

layout(set = 1, binding = 1) uniform sampler2D tex;


vec3 Diffuse(vec3 Norm, vec3 lightPos, vec3 Color) {
	vec3 direction = normalize(lightPos - fragPos);
	vec3 directionViewer = normalize(subo.eyePos - fragPos);
	float A, B, G, alpha, beta, tethai, tethar;
	vec3 vi, vr, L;
	
	A = 1.0f - 0.5f * ((subo.rff.x * subo.rff.x) / ((subo.rff.x * subo.rff.x) + 0.33f));
	B = 0.45 * ((subo.rff.x * subo.rff.x) / ((subo.rff.x * subo.rff.x) + 0.9f));
	
	tethai = acos( dot(direction, Norm) );
	tethar = acos( dot(directionViewer, Norm) );
	
	alpha = max(tethai, tethar);
	beta =  min(tethai, tethar);
	
	vi = normalize(direction - dot(direction, Norm) * Norm);
	vr = normalize(directionViewer - dot(directionViewer, Norm) * Norm);
	
	G = max(0, dot(vi, vr));
	
	L = Color * clamp(dot(direction, Norm), 0.0f, 1.0f);
	
    return L*(A+B*G*sin(alpha)*tan(beta));
	
}

vec3 Specular(vec3 Norm, vec3 lightPos, vec3 specularColor, vec3 eyeDir) {
    vec3 direction = normalize(lightPos - fragPos);
    vec3 f_specular = specularColor * pow(clamp(dot(eyeDir, -reflect(direction, Norm)), 0.0f, 1.0f), subo.rff.y);
    return f_specular;
}


void main() {
    vec3 norm = normalize(fragNorm);
	vec3 EyeDir = normalize(subo.eyePos - fragPos);
    
    vec3 Albedo = texture(tex, fragUV).rgb;
    
    vec3 diff = Diffuse(norm, subo.lightPos, Albedo);
	
	vec3 spec = Specular(norm, subo.lightPos, subo.lightColor ,EyeDir);
	
    vec3 finalResult = (diff + spec)* subo.lightColor * pow( (2.0f / distance(subo.lightPos, fragPos) ), 0.5); ;
	
    outColor = vec4(finalResult + Albedo * 0.1f, 1.0f) ; 
}
