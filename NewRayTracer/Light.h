#pragma once

#include "Colour.h"

class Light
{
protected:
	Colour intensity;

public:
	Light(Colour const &newIntensity) : intensity(newIntensity) {}

	Colour getIntensity() const { return intensity; }
};
