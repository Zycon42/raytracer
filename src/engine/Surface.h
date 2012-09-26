#pragma once

#include "Canvas.h"

#include <vector>

class Surface : public Canvas
{
public:
	Surface(size_t width, size_t height);
	virtual ~Surface() override;

	virtual size_t width() const override { return _width; }
	virtual size_t height() const override { return _height; }
	virtual const Color& pixel(size_t x, size_t y) const override;
	virtual void setPixel(size_t x, size_t y, const Color& pixel) override;

	enum class Format { RGB32 = 4, RGB16 = 2, RGB8 = 1 };
	void storePixels(void* buffer, Format format = Format::RGB32);
private:
	std::vector<Color> pixels;

	size_t _width;
	size_t _height;
};
