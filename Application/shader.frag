#version 130

uniform sampler2D tex;

in vec2 f_texcoord;

void main() {
	gl_FragColor = texture(tex, f_texcoord);
	//gl_FragColor[0] = gl_FragCoord.x/640.0;
	//gl_FragColor[1] = gl_FragCoord.y/480.0;
	//gl_FragColor[2] = 0.5;
}