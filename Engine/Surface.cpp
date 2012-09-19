#include "stdafx.h"
#include "Surface.h"

#include <cassert>
#include <functional>
#include <map>

Surface::Surface(size_t width, size_t height) : pixels(width * height), 
	_height(height), _width(width) {
}


Surface::~Surface()
{
}

const Color& Surface::pixel(size_t x, size_t y) const {
	assert(x < width() && y < height());
	return pixels[y * width() + x];
}

void Surface::setPixel(size_t x, size_t y, const Color& pixel) {
	assert(x < width() && y < height());
	pixels[y * width() + x] = pixel;
}

static uint8_t round(float number) {
	return uint8_t(number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5));
}

void Surface::storePixels(void* buffer, Format format /* = Format::RGB32 */) {
	std::map<Format, std::function<void (const Color&, void*)>> map;
	map[Format::RGB32] = [] (const Color& col, void* p) {
		uint8_t* buff = (uint8_t*)p;
		buff[3] = 0; buff[0] = round(col.r * UINT8_MAX);
		buff[1] = round(col.g * UINT8_MAX); buff[2] = round(col.b * UINT8_MAX);
	};
	map[Format::RGB16] = [] (const Color& col, void* p) {
		uint16_t* buff = (uint16_t*)p;
		buff[0] = (round(col.b * 32) & 0x1fui8) | ((round(col.g * 64) & 0x3fui8) << 5) |
			((round(col.r * 32) & 0x1fui8) << 11);
	};
	map[Format::RGB8] = [] (const Color& col, void* p) {
		uint8_t* buff = (uint8_t*)p;
		buff[0] = (round(col.b * 4) & 0x3ui8) | ((round(col.g * 8) & 0x7ui8) << 2) |
			((round(col.r * 8) & 0x7ui8) << 5);
	};

	for (auto pix : pixels) {
		map[format](pix, buffer);
		buffer = (char*)buffer + static_cast<int>(format);
	}
}
