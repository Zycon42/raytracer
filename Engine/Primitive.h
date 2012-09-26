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
	Sphere(const Vector3f& center, float radius) : center(center), radius(radius) {}

	bool intersects(const Ray& ray, float* dist) {
		Vector3f v = ray.origin() - center;
		float b = -v.dot(ray.direction());
		float det = (b * b) - v.dot(v) + (radius * radius);
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
	Vector3f center;
	float radius;
};
