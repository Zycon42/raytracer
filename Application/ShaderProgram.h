#pragma once

class ShaderProgram
{
public:
	explicit ShaderProgram(const std::string& name);
	~ShaderProgram();

	void bindAttribLocation(GLuint index, const char* name) {
		glBindAttribLocation(program, index, name);
	}

	void use() {
		glUseProgram(program);
	}

	void link();

	void setUniform(const char* name, int value) {
		GLint loc = glGetUniformLocation(program, name);
		glUniform1i(loc, value);
	}
private:
	ShaderProgram(const ShaderProgram&);
	ShaderProgram& operator=(const ShaderProgram&);

	void compileShader(GLuint shader, const std::string& fileName);

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;
};
