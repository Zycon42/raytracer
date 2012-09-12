#pragma once

struct Color 
{
	Color() : r(0.0), g(0.0), b(0.0) {}
	Color(float r, float g, float b) : r(r), g(g), b(b) {}

	float r, g, b;
};

/**
 * Interface for drawable surface.
 */
class Canvas
{
public:
	virtual ~Canvas() { }

	virtual size_t width() = 0;
	virtual size_t height() = 0;
	virtual const Color& pixel(size_t x, size_t y) const = 0;
	virtual void setPixel(size_t x, size_t y, const Color& pixel) = 0;
};
