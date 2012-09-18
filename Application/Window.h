#pragma once

class Window
{
public:
	Window(size_t width, size_t height, const char* caption);

	void run();
private:
	void processEvents();

	SDL_Surface* screen;
	bool done;
};

