#pragma once

class Colour
{
private:
	float r;
	float g;
	float b;
public:
	Colour() : r(0.0f), g(0.0f), b(0.0f) {}
	Colour(float const &newR, float const &newG, float const &newB) : r(newR), g(newG), b(newB) {}

	Colour operator+(Colour const &colour) const { return Colour(r + colour.getR(), g + colour.getG(), b + colour.getB()); }

	Colour operator-(Colour const &colour) const { return Colour(r - colour.getR(), g - colour.getG(), b - colour.getB()); }

	Colour operator*(float const &scalar) const { return Colour(r * scalar, g * scalar, b * scalar); }
	Colour operator*(Colour const &colour) const { return Colour(r * colour.getR(), g * colour.getG(), b * colour.getB()); }

	float getR() const { return r; }
	float getG() const { return g; }
	float getB() const { return b; }
};

