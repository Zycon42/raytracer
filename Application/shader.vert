#version 130

in vec2 in_position;

void main() {
	gl_Position = vec4(in_position.x, in_position.y, 0.0, 0.0);
}
