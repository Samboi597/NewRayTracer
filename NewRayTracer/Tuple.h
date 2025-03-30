#pragma once
class Tuple
{
protected:
	float x;
	float y;
	float z;
	float w;
public:
	Tuple() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Tuple(float const &newX, float const &newY, float const &newZ, float const &newW) : x(newX), y(newY), z(newZ), w(newW) {}

	void setX(float const &newX) { x = newX; }
	void setY(float const &newY) { y = newY; }
	void setZ(float const &newZ) { z = newZ; }
	void setW(float const &newW) { w = newW; }

	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }
	float getW() const { return w; }

	bool operator==(Tuple const &other) const { return x == other.getX() && y == other.getY() && z == other.getZ() && w == other.getW(); }
};

