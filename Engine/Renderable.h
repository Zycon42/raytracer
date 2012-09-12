#pragma once

#include "Canvas.h"

class Ray;

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