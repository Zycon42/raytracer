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
		//float a = ray.direction().dot(ray.direction());
		//float b = 2.0f *ray.direction().dot(ray.origin());
		//float c = ray.origin().dot(ray.origin()) - (radius * radius);

		//float disc = b * b - 4.0f * a * c;

		//// compute q as described above
		//float distSqrt = sqrtf(disc);
		//float q;
		//if (b < 0.0f)
		//	q = (-b - distSqrt)/2.0f;
		//else
		//	q = (-b + distSqrt)/2.0f;

		//// compute t0 and t1
		//float t0 = q / a;
		//float t1 = c / q;

		//// make sure t0 is smaller than t1
		//if (t0 > t1) {
		//	// if t0 is bigger than t1 swap them around
		//	float temp = t0;
		//	t0 = t1;
		//	t1 = temp;
		//}

		//// if t1 is less than zero, the object is in the ray's negative direction
		//// and consequently the ray misses the sphere
		//if (t1 < 0)
		//	return false;

		//// if t0 is less than zero, the intersection point is at t1
		//if (t0 < 0) {
		//	if (dist)
		//		*dist = t1;
		//	return true;
		//// else the intersection point is at t0
		//} else {
		//	if (dist)
		//		*dist = t0;
		//	return true;
		//}
		Vector3f v = ray.origin() - center;
		float b = -v.dot(ray.direction());
		float det = (b * b) - v.dot(v) + (radius * radius);
		if (det > 0)
		{
			det = sqrtf( det );
			float i1 = b - det;
			float i2 = b + det;
			/*if (i2 > 0)
			{
			if (i1 < 0) 
			{
			if (dist)
			*dist = i2;
			return true;
			}
			else
			{
			if (dist)
			*dist = i1;
			return true;
			}
			}*/
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
		return false;
	}
private:
	Vector3f center;
	float radius;
};
