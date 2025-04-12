#pragma once

#include <memory>
#include "Ray.h"
#include "Shape.h"

using namespace std;

class Intersection
{
private:
	float t;
	shared_ptr<Shape const> object;
	Point point;
	Vector eyeV;
	Vector normalV;
	bool inside;

public:
	Intersection() : t(0.0f), object(nullptr), point(Point()), eyeV(Vector()), normalV(Vector()), inside(false) {}
	Intersection(float const& newT, shared_ptr<Shape const> const& newObject) : t(newT), object(newObject), point(Point()), eyeV(Vector()), normalV(Vector()), inside(false) {}
	
	float getT() const { return t; }
	shared_ptr<Shape const> getObject() const { return object; }
	Point getPoint() const { return point; }
	Vector getEyeV() const { return eyeV; }
	Vector getNormalV() const { return normalV; }
	bool isInside() const { return inside; }

	bool has_value() const { return object != nullptr; }
	void prepareComputations(Ray const& r);
};
