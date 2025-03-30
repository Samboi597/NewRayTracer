#pragma once
#include "Colour.h"
#include <vector>

using namespace std;

class Canvas
{
private:
	int width;
	int height;
	vector<Colour> pixels;

public:
	Canvas(int const &newWidth, int const &newHeight) : width(newWidth), height(newHeight), pixels((newWidth * newHeight), Colour(0.0, 0.0, 0.0)) {}
	Canvas(int const& newWidth, int const& newHeight, Colour const& colour) : width(newWidth), height(newHeight), pixels((newWidth* newHeight), colour) {}

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	Colour getPixelColour(int const &x, int const &y) const { return pixels[y * width + x]; }

	void setPixelColour(int const &x, int const &y, Colour const &colour) { pixels[y * width + x] = colour; }
};

