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
