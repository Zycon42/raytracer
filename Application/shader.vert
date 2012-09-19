#version 130

in vec2 position;
in vec2 texcoord;

out vec2 f_texcoord;

void main() {
	f_texcoord = texcoord;
	gl_Position = vec4(position, 0.0, 1.0);
}
