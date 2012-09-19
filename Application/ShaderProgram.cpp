#include "stdafx.h"
#include "ShaderProgram.h"

#include "Exception.h"
#include "File.h"

ShaderProgram::ShaderProgram(const std::string& name) : vertexShader(0), fragmentShader(0) {
	program = glCreateProgram();

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	try {
		compileShader(vertexShader, name + ".vert");
	} catch (Exception& e) {
		LOG(ERROR) << "Failed to load vertex shader: " << e;
		glDeleteShader(vertexShader);
		vertexShader = 0;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	try {
		compileShader(fragmentShader, name + ".frag");
	} catch (Exception& e) {
		LOG(ERROR) << "Failed to load fragment shader: " << e;
		glDeleteShader(fragmentShader);
		fragmentShader = 0;
	}

	if (vertexShader == 0 && fragmentShader == 0)
		throw Exception("Failed to load vertex and fragment shader see log for details");
}

ShaderProgram::~ShaderProgram() {
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderProgram::compileShader(GLuint shader, const std::string& fileName) {
	File file(fileName, File::OpenMode::ReadOnly);
	auto shaderBlob = file.readAll();
	auto shaderData = shaderBlob.data();
	int shaderDataSize = shaderBlob.size();

	glShaderSource(shader, 1, (const GLchar**)&shaderData, &shaderDataSize);
	glAttachShader(program, shader);
	glCompileShader(shader);

	// test if compile successful
	int successful;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &successful);
	if (successful == GL_FALSE) {
		int buffLen;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &buffLen);
		std::unique_ptr<char[]> buff(new char[buffLen]);
		glGetShaderInfoLog(shader, buffLen, nullptr, buff.get());

		throw Exception(("Shader compilation failed. LOG: " + std::string(buff.get())).c_str());
	}
}

void ShaderProgram::link() {
	glLinkProgram(program);

	// test if link successful
	int successful;
	glGetProgramiv(program, GL_LINK_STATUS, &successful);
	if (successful == GL_FALSE) {
		int buffLen;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &buffLen);
		std::unique_ptr<char[]> buff(new char[buffLen]);
		glGetProgramInfoLog(program, buffLen, nullptr, buff.get());

		throw Exception(("Shader program linking failed. LOG: " + std::string(buff.get())).c_str());
	}
}