#pragma once

#include "Renderable.h"

class Light
{
public:
	virtual ~Light() { }

	virtual const Vector3f& position() = 0;
	virtual const Material& material() = 0;
}; 

class PointLight : public Light
{
public:
	PointLight(const Vector3f& pos, const Material& mat) : pos(pos), mat(mat) {}

	virtual const Vector3f& position() override {
		return pos;
	}

	void setPosition(const Vector3f& p) {
		pos = p;
	}

	virtual const Material& material() override {
		return mat;
	}
private:
	Vector3f pos;
	Material mat;
};
