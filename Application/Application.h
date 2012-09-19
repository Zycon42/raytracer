#pragma once

class Buffer;
class ShaderProgram;
class Texture2D;
class Application
{
public:
	Application();
	~Application();

	int run();
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
	std::unique_ptr<Texture2D> texture;
};

