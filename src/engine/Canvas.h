#pragma once

#include <cstddef>

#include "Vector3.h"

class Color : public Vector3f
{
public:
	Color() : Vector3f() { }
	Color(float r, float g, float b) : Vector3f(r, g, b) { }

	/// Access x vector component.
	float& r() { return x(); }
	/// Return x vector component.
	float r() const { return x(); }
	/// Access y vector component.
	float& g() { return y(); }
	/// Return y vector component.
	float g() const { return y(); }
	/// Access z vector component.
	float& b() { return z(); }
	/// Return z vector component.
	float b() const { return z(); }

	static Color black() { return Color(0.0f, 0.0f, 0.0f); }
	static Color white() { return Color(1.0f, 1.0f, 1.0f); }
};

/**
 * Interface for drawable surface.
 */
class Canvas
{
public:
	virtual ~Canvas() { }

	virtual size_t width() const = 0;
	virtual size_t height() const = 0;
	virtual const Color& pixel(size_t x, size_t y) const = 0;
	virtual void setPixel(size_t x, size_t y, const Color& pixel) = 0;
};
