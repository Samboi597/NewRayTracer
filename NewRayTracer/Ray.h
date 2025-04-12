#pragma once

#include "Matrix.h"
#include "Point.h"
#include "Vector.h"

class Ray
{
private:
	Point origin;
	Vector direction;

public:
	Ray() : origin(Point()), direction(Vector()) {}
	Ray(Point const& newOrigin, Vector const& newDirection) : origin(newOrigin), direction(newDirection) {}

	Point getOrigin() const { return origin; }
	Vector getDirection() const { return direction; }
	Point position(float const& t) const { return origin + direction * t; }
	Ray transform(Matrix const& matrix) const { return Ray(matrix * origin, matrix * direction); }
};
