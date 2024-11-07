shader_type spatial;

uniform sampler2D texture_albedo : hint_albedo;
uniform sampler2D texture_metallic;
uniform sampler2D texture_rough;

void fragment() {
	vec4 sampled_albedo = texture(texture_albedo, UV) * COLOR;
	ALBEDO = sampled_albedo.rgb;
	ALPHA = sampled_albedo.a;
	METALLIC = texture(texture_metallic, UV).r;
	ROUGHNESS = texture(texture_rough, UV).r;
}
