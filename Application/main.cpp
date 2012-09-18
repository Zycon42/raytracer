#include "stdafx.h"

#include "Exception.h"
#include "Window.h"

int main(int argc, char *argv[]) {
	google::InitGoogleLogging(argv[0]);

	SDL_Init(SDL_INIT_VIDEO);  
	atexit(SDL_Quit);

	try {
		Window wnd(640, 480, "Title");
		wnd.run();
	} catch (Exception& e) {
		LOG(FATAL) << "Unhandled exception" << e;
	}

	return 0;
}