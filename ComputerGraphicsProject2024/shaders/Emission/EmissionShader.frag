#version 450#extension GL_ARB_separate_shader_objects : enable
layout(set = 0, binding = 2) uniform EmissionColorUniformBuffer {	vec4 color;} ubo;
layout(location = 0) in vec2 fragUV;
layout(location = 0) out vec4 outColor;layout(set = 0, binding = 1) uniform sampler2D tex;void main() {
	vec3 Emit = texture(tex, fragUV).rgb;			outColor = vec4(Emit * ubo.color.xyz, 1.0f);	}