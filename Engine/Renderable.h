#pragma once

#include "Canvas.h"
#include "Primitive.h"

struct Material 
{
	Color ambient;
};

class Renderable
{
public:
	virtual ~Renderable() {}

	virtual const Material& material() = 0;
	virtual bool intersects(const Ray& ray, float* dist = nullptr) = 0;
};

class SphereObject : public Renderable
{
public:
	SphereObject(const Vector3f& center, float radius) : sphere(center, radius) {}

	virtual const Material& material() override {
		return mat;
	}

	void setMaterial(const Material& mat) {
		this->mat = mat;
	}

	virtual bool intersects(const Ray& ray, float* dist = nullptr) override {
		return sphere.intersects(ray, dist);
	}
private:
	Sphere sphere;
	Material mat;
};
