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
		LOG(ERROR) << "Failed to load vertex shader " << e;
		glDeleteShader(vertexShader);
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	try {
		compileShader(fragmentShader, name + ".frag");
	} catch (Exception& e) {
		LOG(ERROR) << "Failed to load fragment shader " << e;
		glDeleteShader(fragmentShader);
	}
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

	// store log
	int buffLen;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &buffLen);
	std::unique_ptr<char[]> buff(new char[buffLen]);
	glGetShaderInfoLog(shader, buffLen, nullptr, buff.get());
	log += buff.get();
}

void ShaderProgram::bindAttribLocation(GLuint index, const char* name) {
	glBindAttribLocation(program, index, name);
}

void ShaderProgram::use() {
	glUseProgram(program);
}

void ShaderProgram::link() {
	glLinkProgram(program);

	// store log
	int buffLen;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &buffLen);
	std::unique_ptr<char[]> buff(new char[buffLen]);
	glGetProgramInfoLog(program, buffLen, nullptr, buff.get());
	log += buff.get();
}