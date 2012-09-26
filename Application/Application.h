#pragma once

class Buffer;
class ShaderProgram;
class Texture2D;
class Surface;
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
	void update();
	void init();

	void beginScene();
	void endScene();

	static double getTime();

	static const char* WND_TITLE;

	SDL_Surface* screen;
	bool done;

	bool rendererDone;
	double time;

	std::unique_ptr<Buffer> vbo;
	std::unique_ptr<ShaderProgram> shader;
	std::unique_ptr<Texture2D> texture;
	std::shared_ptr<Surface> surface;
};

