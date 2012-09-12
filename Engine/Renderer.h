#pragma once

#include "Primitive.h"
#include "Canvas.h"

class Scene;
class Renderable;

class Renderer
{
public:
	Renderer(const std::shared_ptr<Scene>& scene, const std::shared_ptr<Canvas>& canvas);

	void setCanvas(const std::shared_ptr<Canvas>& canvas) { this->canvas = canvas; }

	void render();
private:
	Ray spawnRay(size_t x, size_t y);
	Color rayTrace(const Ray& ray, size_t depth = 0);
	std::shared_ptr<Renderable> findNearestRenderable(const Ray& ray, float& distance);

	std::shared_ptr<Scene> scene;
	std::shared_ptr<Canvas> canvas;
};
