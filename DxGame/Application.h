#pragma once

#include "Window.h"
#include "D3D.h"

class Application
{
public:
	Application(HINSTANCE hInstance);

	int run();
private:
	/// Class name for windows call @link{RegisterClassEx}
	static LPCTSTR CLASS_NAME;
	/// Window title
	static LPCTSTR WND_TITLE;

	void init(int width, int height);
	void renderFrame();

	HINSTANCE hInstance;
	Window window;
	D3D d3d;
};
