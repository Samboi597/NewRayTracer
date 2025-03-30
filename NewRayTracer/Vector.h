#pragma once
#include <cmath>
#include "Tuple.h"

class Vector :
    public Tuple
{
public:
    Vector(float const &newX, float const &newY, float const &newZ) : Tuple(newX, newY, newZ, 0.0f) {}

    Vector operator+(Vector const &vector) const { return Vector(x + vector.getX(), y + vector.getY(), z + vector.getZ()); }

	Vector operator-() const { return Vector(-x, -y, -z); }
    Vector operator-(Vector const &vector) const { return Vector(x - vector.getX(), y - vector.getY(), z - vector.getZ()); }

	Vector operator*(float const &scalar) const { return Vector(x * scalar, y * scalar, z * scalar); }

	Vector operator/(float const &scalar) const { return Vector(x / scalar, y / scalar, z / scalar); }

	float magnitude() const { return sqrt(x * x + y * y + z * z); }

	Vector normalise() const { float mag = magnitude(); return Vector(x / mag, y / mag, z / mag); }

	float dot(Vector const &vector) const { return (x * vector.getX() + y * vector.getY() + z * vector.getZ()); }

	Vector cross(Vector const &vector) const { return Vector(y * vector.getZ() - z * vector.getY(), z * vector.getX() - x * vector.getZ(), x * vector.getY() - y * vector.getX()); }
};

