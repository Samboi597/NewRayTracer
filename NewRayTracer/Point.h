#pragma once
#include "Tuple.h"
#include "Vector.h"

class Point :
    public Tuple
{
public:
    Point(float const &newX, float const &newY, float const &newZ) : Tuple(newX, newY, newZ, 1.0f) {}

    Point operator+(Vector const &vector) const { return Point(x + vector.getX(), y + vector.getY(), z + vector.getZ()); }

    Point operator-(Vector const &vector) const { return Point(x - vector.getX(), y - vector.getY(), z - vector.getZ()); }
	Vector operator-(Point const &point) const { return Vector(x - point.getX(), y - point.getY(), z - point.getZ()); }
};

