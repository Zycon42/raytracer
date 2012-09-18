#include "stdafx.h"
#include "Application.h"

#include "Exception.h"

Application::Application() : screen(nullptr), done(false) {
	GLenum err;
	if ((err = glewInit()) != GLEW_OK)
		throw Exception((const char*)glewGetErrorString(err));

	LOG(INFO) << "Using GLEW " << glewGetString(GLEW_VERSION);
}

void Application::init(size_t width, size_t height, const char* caption) {
	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
	if (!screen)
		throw Exception(SDL_GetError());

	SDL_WM_SetCaption(caption, nullptr);
}

void Application::run() {
	while (!done) {
		processEvents();
	}
}

void Application::processEvents() {
	SDL_Event event;  
	while(SDL_PollEvent(&event)) {
		switch (event.type)  
		{  
		case SDL_QUIT:
			done = true; 
			break;  
		case SDL_KEYDOWN: 
			switch(event.key.keysym.sym)  
			{  
			case SDLK_ESCAPE:
				SDL_Event quitEvent = { SDL_QUIT };
				SDL_PushEvent(&quitEvent);
				break;
			}  
			break;  
		}  
	}
}
