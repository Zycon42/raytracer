#pragma once

class Buffer
{
public:
	explicit Buffer(GLenum target = GL_ARRAY_BUFFER) : target(target) {
		glGenBuffers(1, &buf);
	}

	~Buffer() {
		glDeleteBuffers(1, &buf);
	}

	void bind() {
		glBindBuffer(target, buf);
	}

	void loadData(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW) {
		glBindBuffer(target, buf);
		glBufferData(target, size, data, usage);
	}
private:
	Buffer(const Buffer&);
	Buffer& operator=(const Buffer&);

	GLuint buf;
	GLenum target;
};

