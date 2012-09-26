#pragma once

#include "Primitive.h"
#include "Canvas.h"

#include <memory>

class Scene;
class Renderable;

class Renderer
{
public:
	Renderer(const std::shared_ptr<Scene>& scene);

	void render(const std::shared_ptr<Canvas>& canvas);
private:
	Ray spawnRay(float x, float y);
	Color rayTrace(const Ray& ray, size_t depth = 0);
	std::shared_ptr<Renderable> findNearestRenderable(const Ray& ray, float& distance);

	std::shared_ptr<Scene> scene;
};
