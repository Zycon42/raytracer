#include "stdafx.h"
#include "Application.h"

#include "Exception.h"
#include "Surface.h"
#include "Scene.h"
#include "Renderer.h"

#include "Buffer.h"
#include "ShaderProgram.h"
#include "Texture2D.h"

#ifdef _WIN32
// without NOGDI there's name conflict with glog (windows define ERROR macro)
#define NOGDI
#include <Windows.h>
#endif // _WIN32

const char* Application::WND_TITLE = "Raytracer";

struct Vertex
{
	float pos[2];
	float texCoords[2];
};

Application::Application() : screen(nullptr), done(false), rendererDone(false) {
	createWindow(800, 600);
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
	Vertex vertices[] = {
		{{-1.0f,  1.0f}, {0.0f,  1.0f}},
		{{-1.0f, -1.0f}, {0.0f, 0.0f}}, 
		{{1.0f, -1.0f}, {1.0f, 0.0f}},
		{{1.0f,  1.0f}, {1.0f,  1.0f}},
		{{-1.0f, 1.0f}, {0.0f, 1.0f}},
		{{1.0f, -1.0f}, {1.0f, 0.0f}}
	};
	vbo.reset(new Buffer());
	vbo->loadData(vertices, sizeof(vertices));

	// bind vbo to gpu
	vbo->bind();
	// tell gpu vertex declaration
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, pos)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoords)));

	// create shader program
	shader.reset(new ShaderProgram("shader"));
	shader->bindAttribLocation(0, "position");
	shader->bindAttribLocation(1, "texcoord");
	shader->link();
	shader->use();
	shader->setUniform("tex", 0);		// set first texture unit
	LOG(INFO) << "Shaders compiled successfully.";
	
	// raytrace in another thread
	auto scene = std::make_shared<Scene>();		// create scene in this thread so exceptions will be delivered here.
	surface = std::make_shared<Surface>(screen->h, screen->w);
	std::thread thread([&] () { 
		Renderer renderer(scene); 
		renderer.render(surface);
		rendererDone = true;
	});
	thread.detach();
	LOG(INFO) << "Raytracing started in new thread [" << thread.get_id() << "].";

	time = getTime();
}

void Application::update() {
	// when renderer finished.
	if (rendererDone) {
		rendererDone = false;

		LOG(INFO) << "Raytracing has ended in " << getTime() - time << " sec";

		// store raytracer output to temp buffer
		std::unique_ptr<char[]> temp(new char[surface->width() * surface->height() * 4]);
		surface->storePixels(temp.get());

		// create texture from temp buffer
		texture.reset(new Texture2D());
		//std::vector<Texture2D::Param> params;	// MSVC 2012 doesn't support C++11 initializer lists yet :(
		//params.push_back(Texture2D::Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		std::array<Texture2D::Param, 1> params = { Texture2D::Param(GL_TEXTURE_MIN_FILTER, GL_LINEAR) };
		texture->loadData(params, surface->width(), surface->height(), temp.get());

		// bind texture to first texturing unit
		glActiveTexture(GL_TEXTURE0);
		texture->bind();
	}
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
			update();
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

double Application::getTime() {
#ifdef _WIN32
	// windows version
	static LARGE_INTEGER freq;
	static bool first = true;
	if (first) {
		first = false;
		if (!QueryPerformanceFrequency(&freq))
			throw Win32Exception("QueryPerformanceFrequency failed!");
	}

	LARGE_INTEGER val;
	QueryPerformanceCounter(&val);
	return static_cast<double>(val.QuadPart) / static_cast<double>(freq.QuadPart);
#else
	// posix version
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == -1)
		throw SystemException("gettimeofday failed!");

	return static_cast<double>(tv.tv_sec) + static_cast<double>(tv.tv_usec) / 1000000.0;
#endif // _WIN32
}