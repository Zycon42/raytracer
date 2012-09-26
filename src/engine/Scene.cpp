#include "Scene.h"

#include "Renderable.h"

Scene::Scene() {
	Material mat;
	mat.ambient = Color(0.7f, 0.7f, 0.7f);

	auto sphere1 = std::make_shared<SphereObject>(Vector3f(1.0f, -0.8f, 3.0f), 2.5f);
	sphere1->setMaterial(mat);
	_renderables.push_back(sphere1);

	auto sphere2 = std::make_shared<SphereObject>(Vector3f(-5.5f, -0.5f, 7.0f), 2.0f);
	mat.ambient = Color(0.7f, 0.7f, 1.0f);
	sphere2->setMaterial(mat);
	_renderables.push_back(sphere2);
}