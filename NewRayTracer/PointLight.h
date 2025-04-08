#pragma once

#include "Light.h"
#include "Point.h"

class PointLight :
    public Light
{
private:
    Point position;

public:
    PointLight(Point const& newPosition, Colour const& newIntensity) : position(newPosition), Light(newIntensity) {}

	Point getPosition() const { return position; }
};

