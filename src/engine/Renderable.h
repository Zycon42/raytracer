#pragma once

#include "Canvas.h"
#include "Primitive.h"

/// Renderable material properties for light model.
struct Material 
{
	Material(Color ambient = Color(), Color diffuse = Color(), Color specular = Color(), float shininess = 1.0f) : ambient(ambient),
		diffuse(diffuse), specular(specular), shininess(shininess)
	{}

	Color ambient;
	Color diffuse;
	Color specular;
	float shininess;
};

class Renderable
{
public:
	virtual ~Renderable() {}

	virtual const Material& material() = 0;
	virtual bool intersects(const Ray& ray, float* dist = nullptr) = 0;
	virtual Vector3f normal(const Vector3f& p) = 0;
};

class RenderableObject : public Renderable
{
public:
	virtual const Material& material() override {
		return mat;
	}

	void setMaterial(const Material& mat) {
		this->mat = mat;
	}
private:
	Material mat;
};

class SphereObject : public RenderableObject
{
public:
	SphereObject(const Vector3f& center, float radius) : sphere(center, radius) {}

	virtual bool intersects(const Ray& ray, float* dist = nullptr) override {
		return sphere.intersects(ray, dist);
	}

	virtual Vector3f normal(const Vector3f& p) override {
		return (p - sphere.center()) * (1.0f / sphere.radius());
	}
private:
	Sphere sphere;
};

class PlaneObject : public RenderableObject
{
public:
	PlaneObject(const Vector3f& n, float d) : plane(n, d) {}

	virtual bool intersects(const Ray& ray, float* dist /* = nullptr */) override {
		return plane.intersects(ray, dist);
	}

	virtual Vector3f normal(const Vector3f& p) override {
		// plane normal is same for each point
		return plane.normal();
	}
protected:
	Plane plane;
};
