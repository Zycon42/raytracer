#include "stdafx.h"

#include "Exception.h"
#include "Application.h"

int main(int argc, char *argv[]) {
	google::InitGoogleLogging(argv[0]);

	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);

	try {
		Application app;
		app.init(640, 480, "Title");
		app.run();
	} catch (Exception& e) {
		LOG(FATAL) << "Unhandled exception " << e;
	}

	return 0;
}