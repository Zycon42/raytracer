#pragma once

#include <cstddef>

struct Color 
{
	Color() : r(0.0f), g(0.0f), b(0.0f) {}
	Color(float r, float g, float b) : r(r), g(g), b(b) {}

	float r, g, b;

	static Color white() { return Color(1.0f, 1.0f, 1.0f); }
	static Color black() { return Color(0.0f, 0.0f, 0.0f); }
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
