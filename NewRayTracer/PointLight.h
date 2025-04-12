#pragma once

#include "Light.h"

class PointLight : public Light
{
private:
    Point position;

public:
    PointLight(Point const& newPosition, Colour const& newIntensity) : position(newPosition), Light(newIntensity) {}

    Point getPosition() override { return position; }
};
