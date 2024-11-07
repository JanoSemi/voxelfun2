shader_type spatial;

uniform sampler2D texture_albedo : hint_albedo;
uniform sampler2D texture_metallic;
uniform sampler2D texture_rough;

void fragment() {
	ALBEDO = texture(texture_albedo, UV).rgb * COLOR.rgb;
	METALLIC = texture(texture_metallic, UV).r;
	ROUGHNESS = texture(texture_rough, UV).r;
}
