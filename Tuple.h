#pragma once
class Tuple
{
protected:
	float x;
	float y;
	float z;
	float w;
public:
	Tuple(float const &newX, float const &newY, float const &newZ, float const &newW) : x(newX), y(newY), z(newZ), w(newW) {}

	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }
	float getW() const { return w; }
};

