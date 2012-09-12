#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer(std::shared_ptr<Scene> scene, std::shared_ptr<Canvas> canvas)
	: scene(scene), canvas(canvas) {
}

Ray Renderer::spawnRay(size_t x, size_t y) {
	static Vector3f org(0.0f, 0.0f, -5.0f);

	Vector3f dir = Vector3f(x, y, 0.0f) - org;
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

}