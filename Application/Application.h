#pragma once

class Buffer;
class ShaderProgram;
class Application
{
public:
	Application();
	~Application();

	void run();
private:
	void createWindow(size_t width, size_t height);
	void processEvents();
	void draw();
	void init();

	void beginScene();
	void endScene();

	static const char* WND_TITLE;

	SDL_Surface* screen;
	bool done;

	std::unique_ptr<Buffer> vbo;
	std::unique_ptr<ShaderProgram> shader;
};

