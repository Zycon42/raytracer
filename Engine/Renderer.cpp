#include "stdafx.h"
#include "Renderer.h"

#include "Scene.h"
#include "Renderable.h"

Renderer::Renderer(const std::shared_ptr<Scene>& scene, const std::shared_ptr<Canvas>& canvas)
	: scene(scene), canvas(canvas) {
}

Ray Renderer::spawnRay(size_t x, size_t y) {
	static Vector3f org(0.0f, 0.0f, -5.0f);

	Vector3f dir = Vector3f(static_cast<float>(x), static_cast<float>(y), 0.0f) - org;
	dir.normalize();
	return Ray(org, dir);
}

void Renderer::render() {
	for (size_t x = 0; x < canvas->width(); x++) {
		for (size_t y = 0; y < canvas->height(); y++) {
			canvas->setPixel(x, y, rayTrace(spawnRay(x, y)));
		}
	}
}

Color Renderer::rayTrace(const Ray& ray, size_t depth) {
	auto color = Color::black();

	float distance = std::numeric_limits<float>::max();
	auto renderable = findNearestRenderable(ray, distance);
	if (!renderable)
		return color;

	//Vector3f hitPt = ray.origin() + ray.direction() * distance;
	color = renderable->material().ambient;

	return color;
}

std::shared_ptr<Renderable> Renderer::findNearestRenderable(const Ray& ray, float& distance) {
	std::shared_ptr<Renderable> out;

	for (auto renderable : scene->renderables()) {
		float newDist;
		if (renderable->intersects(ray, &newDist)) {
			if (distance < newDist) {
				distance = newDist;
				out = renderable;
			}
		}
	}
	return out;
}