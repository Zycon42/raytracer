#include "Renderer.h"

#include "Scene.h"
#include "Renderable.h"
#include "Light.h"

Renderer::Renderer(const std::shared_ptr<Scene>& scene)
	: scene(scene) {
}

Ray Renderer::spawnRay(float x, float y) {
	static Vector3f org(0.0f, 0.0f, -5.0f);

	Vector3f dir = Vector3f(x, y, 0.0f) - org;
	dir.normalize();
	return Ray(org, dir);
}

void Renderer::render(const std::shared_ptr<Canvas>& canvas) {
	float screenPlaneX = -4.0f, screenPlaneY = -3.0f;
	float screenPlaneWidth = 8.0f, screenPlaneHeight = 6.0f;
	float dx = screenPlaneWidth / canvas->width();
	float dy = screenPlaneHeight / canvas->height();

	float sy = screenPlaneY;
	for (size_t y = 0; y < canvas->height(); y++) {
		float sx = screenPlaneX;
		for (size_t x = 0; x < canvas->width(); x++) {
			canvas->setPixel(x, y, rayTrace(spawnRay(sx, sy)));
			sx += dx;
		}
		sy += dy;
	}
}

Color Renderer::rayTrace(const Ray& ray, size_t depth) {
	auto color = Color::black();

	float distance = std::numeric_limits<float>::max();
	auto renderable = findNearestRenderable(ray, distance);
	if (!renderable)
		return color;

	Vector3f hitPt = ray.origin() + ray.direction() * distance;
	
	Color lightsAmbient;
	for (auto& light : scene->lights()) {
		lightsAmbient += light->material().ambient;

		// calculate dot product of surface normal and vector to light
		Vector3f toLight = light->position() + hitPt;
		toLight.normalize();
		Vector3f norm = renderable->normal(hitPt);
		norm.normalize();
		float dot = toLight.dot(norm);

		if (dot > 0)
			color += dot * renderable->material().diffuse * light->material().diffuse;
	}
	color += renderable->material().ambient * lightsAmbient;

	return color;
}

std::shared_ptr<Renderable> Renderer::findNearestRenderable(const Ray& ray, float& distance) {
	std::shared_ptr<Renderable> out;

	for (auto& renderable : scene->renderables()) {
		float newDist;
		if (renderable->intersects(ray, &newDist)) {
			if (newDist < distance) {
				distance = newDist;
				out = renderable;
			}
		}
	}
	return out;
}