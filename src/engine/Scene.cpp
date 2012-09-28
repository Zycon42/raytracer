#include "Scene.h"

#include "Renderable.h"
#include "Light.h"

Scene::Scene() {
	auto sphere1 = std::make_shared<SphereObject>(Vector3f(1.0f, -0.8f, 3.0f), 2.5f);
	sphere1->setMaterial(Material(Color(0.2f, 0.2f, 0.2f), Color(1.0f, 1.0f, 0.0)));
	renderables().push_back(sphere1);

	auto sphere2 = std::make_shared<SphereObject>(Vector3f(-5.5f, -0.5f, 7.0f), 2.0f);
	sphere2->setMaterial(Material(Color(0.2f, 0.2f, 0.2f), Color(0.0f, 1.0f, 1.0f)));
	renderables().push_back(sphere2);

	auto plane = std::make_shared<PlaneObject>(Vector3f(0.0f, 1.0f, 0.0f), 4.4f);
	plane->setMaterial(Material(Color(0.1f, 0.1f, 0.1f), Color(1.0f, 0.0f, 1.0f)));
	renderables().push_back(plane);

	auto light1 = std::make_shared<PointLight>(Vector3f(0.0f, 5.0f, -5.0f), 
		Material(Color(0.2f, 0.2f, 0.2f), Color(0.4f, 0.4f, 0.4f)));
	lights().push_back(light1);

	auto light2 = std::make_shared<PointLight>(Vector3f(-2.0f, 5.0f, 1.0f), 
		Material(Color(0.2f, 0.2f, 0.2f), Color(0.6f, 0.7f, 1.0f)));
	lights().push_back(light2);
}