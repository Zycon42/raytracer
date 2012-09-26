#include "Application.h"

#include <SDL.h>
#pragma warning(push)
#pragma warning(disable : 4244)
#include <glog/logging.h>
#pragma warning(pop)

int main(int argc, char *argv[]) {
	google::InitGoogleLogging(argv[0]);

	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);

	try {
		Application app;
		return app.run();
	} catch (std::exception& e) {
		LOG(FATAL) << "Unhandled exception " << e.what();
		return 1;
	}
}