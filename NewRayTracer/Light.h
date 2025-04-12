#pragma once

#include "Colour.h"
#include "Point.h"

class Light
{
protected:
	Colour intensity;

public:
	Light(Colour const &newIntensity) : intensity(newIntensity) {}

	Colour getIntensity() const { return intensity; }

	virtual Point getPosition() { return Point(0.0f, 0.0f, 0.0f); }
};
