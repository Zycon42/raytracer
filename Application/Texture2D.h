#pragma once

class Texture2D
{
public:
	struct Param
	{
		Param(GLenum name, GLint value) : name(name), value(value) {}
		GLenum name;
		GLint value;
	};

	Texture2D() {
		glGenTextures(1, &texID);
	}

	~Texture2D() {
		glDeleteTextures(1, &texID);
	}

	void bind() {
		glBindTexture(GL_TEXTURE_2D, texID);
	}

	void loadData(const std::vector<Param>& params, size_t width, size_t height, const void* data) {
		bind();
		for (auto param : params)
			glTexParameteri(GL_TEXTURE_2D, param.name, param.value);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
private:
	Texture2D(const Texture2D&);
	Texture2D& operator=(const Texture2D&);

	GLuint texID;
};

