#pragma once

#include "Primitive.h"
#include "Canvas.h"

class Scene;

class Renderer
{
public:
	Renderer(std::shared_ptr<Scene> scene, std::shared_ptr<Canvas> canvas);

	void setCanvas(std::shared_ptr<Canvas> canvas) { this->canvas = canvas; }

	void render();
private:
	Ray spawnRay(size_t x, size_t y);
	Color rayTrace(const Ray& ray, size_t depth = 0);

	std::shared_ptr<Scene> scene;
	std::shared_ptr<Canvas> canvas;
};
