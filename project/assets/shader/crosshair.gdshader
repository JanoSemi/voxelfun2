shader_type canvas_item;

void fragment() {
	vec4 color = vec4(1.0) - texture(SCREEN_TEXTURE, SCREEN_UV);
	color.a = 1.0;
	COLOR = color;
}
