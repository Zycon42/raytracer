#pragma once

class ShaderProgram
{
public:
	explicit ShaderProgram(const std::string& name);
	~ShaderProgram();

	void bindAttribLocation(GLuint index, const char* name);
	void use();
	void link();
private:
	ShaderProgram(const ShaderProgram&);
	ShaderProgram& operator=(const ShaderProgram&);

	void compileShader(GLuint shader, const std::string& fileName);

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;
};