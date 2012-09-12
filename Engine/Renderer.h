#pragma once

#include "Primitive.h"
#include "Drawable.h"

class Scene;

class Renderer
{
public:
	Renderer(std::shared_ptr<Scene> scene, std::shared_ptr<Drawable> canvas);

	void setCanvas(std::shared_ptr<Drawable> canvas) { this->canvas = canvas; }

	void render();
private:
	Ray spawnRay(size_t x, size_t y);
	Color rayTrace(const Ray& ray, size_t depth = 0);

	std::shared_ptr<Scene> scene;
	std::shared_ptr<Drawable> canvas;
};
