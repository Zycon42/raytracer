#include "stdafx.h"
#include "Window.h"

#include "Exception.h"

Window::Window(size_t width, size_t height, const char* caption) : done(false) {
	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
	if (!screen)
		throw Exception(SDL_GetError());

	SDL_WM_SetCaption(caption, nullptr);
}

void Window::run() {
	while (!done) {
		processEvents();
	}
}

void Window::processEvents() {
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