#pragma once

#include <memory>
#include <vector>
#include "Intersection.h"
#include "Ray.h"
#include "Shape.h"

using namespace std;

class Sphere : public Shape
{
private:
	Point center;
	float radius;

public:
	Sphere() : center(Point(0.0f, 0.0f, 0.0f)), radius(1.0f) {}
	Sphere(Point const& newCenter, float const& newRadius) : center(newCenter), radius(newRadius) {}

	Point getCenter() const override { return center; }
	float getRadius() const override { return radius; }

	void intersect(Ray const& ray, vector<Intersection>& xs) const;
	Vector normalAt(Point const& point) const override;
};
