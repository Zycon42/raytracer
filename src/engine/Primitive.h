#pragma once

#include "Vector3.h"

class Ray
{
public:
	Ray() : org(), dir() {}
	Ray(const Vector3f& org, const Vector3f& dir) : org(org), dir(dir) {}

	const Vector3f& origin() const { return org; }
	void setOrigin(const Vector3f& v) { org = v; }
	const Vector3f& direction() const { return dir; }
	void setDirection(const Vector3f& v) { dir = v; }
private:
	Vector3f org;
	Vector3f dir;
};

class Sphere
{
public:
	Sphere(const Vector3f& center, float radius) : _center(center), _radius(radius) {}

	const Vector3f& center() const { return _center; }
	Vector3f& center() { return _center; }

	float radius() const { return _radius; }
	void setRadius(float r) { _radius = r; }

	bool intersects(const Ray& ray, float* dist) {
		Vector3f v = ray.origin() - center();
		float b = -v.dot(ray.direction());
		float det = (b * b) - v.dot(v) + (radius() * radius());
		if (det < 0)
			return false;

		det = sqrtf( det );
		float i1 = b - det;
		float i2 = b + det;
		bool retval = false;
		float d = std::numeric_limits<float>::max();
		if (i1 > 0 && i1 < d) {
			d = i1;
			retval = true;
		}
		if (i2 > 0 && i2 < d) {
			d = i2;
			retval = true;
		}
			
		if (dist)
			*dist = d;
		return retval;
	}
private:
	Vector3f _center;
	float _radius;
};

class Plane
{
public:
	Plane(const Vector3f& n, float d) : _normal(n), _d(d) { }

	const Vector3f& normal() const { return _normal; }
	Vector3f& normal() { return _normal; }

	float d() const { return _d; }
	void setD(float d) { _d = d; }

	bool intersects(const Ray& ray, float* dist) {
		float dot = normal().dot(ray.direction());
		if (dot > 0) {
			if (dist)
				*dist = -(normal().dot(ray.origin()) + d()) / dot;
			return true;
		}
		return false;
	}
private:
	Vector3f _normal;
	float _d;
};