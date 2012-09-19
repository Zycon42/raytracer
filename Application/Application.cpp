#include "stdafx.h"
#include "Application.h"

#include "Exception.h"
#include "Surface.h"
#include "Scene.h"
#include "Renderer.h"

#include "Buffer.h"
#include "ShaderProgram.h"

const char* Application::WND_TITLE = "Raytracer";

Application::Application() : screen(nullptr), done(false) {
	createWindow(640, 480);
}

Application::~Application() {
}

void Application::createWindow(size_t width, size_t height) {
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
	if (!screen)
		throw Exception(SDL_GetError());

	SDL_WM_SetCaption(WND_TITLE, nullptr);

	GLenum err;
	if ((err = glewInit()) != GLEW_OK)
		throw Exception((const char*)glewGetErrorString(err));

	LOG(INFO) << "Using GLEW " << glewGetString(GLEW_VERSION);
}

void Application::init() {
	glViewport(0, 0, screen->w, screen->h);

	// create and bind vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// create vbo
	float vertices[] = {
		-1.0f,  1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f,
		1.0f,  1.0f,
		-1.0f, 1.0f,
		1.0f, -1.0f
	};
	vbo.reset(new Buffer());
	vbo->loadData(vertices, sizeof(vertices));

	// bind vbo to gpu
	glEnableVertexAttribArray(0);
	vbo->bind();
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	shader.reset(new ShaderProgram("shader"));
	shader->bindAttribLocation(0, "in_position");
	shader->link();
	shader->use();
	LOG(INFO) << "Shaders compiled successfully.";

	//auto surface = std::make_shared<Surface>(screen->h, screen->w);
	//auto scene = std::make_shared<Scene>();

	//Renderer renderer(scene, surface);
	//renderer.render();					// TODO: run in another thread
}

void Application::draw() {
	beginScene();

	glDrawArrays(GL_TRIANGLES, 0, 6);

	endScene();
}

void Application::beginScene() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Application::endScene() {
	GLenum err;
	if ((err = glGetError()) != GL_NO_ERROR)
		throw Exception((const char*)gluErrorString(err));

	SDL_GL_SwapBuffers();
}

int Application::run() {
	try {
		init();
	
		while (!done) {
			processEvents();
			draw();
		}
	} catch (Exception& e) {
		LOG(ERROR) << e;
		return 1;
	}
	return 0;
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
