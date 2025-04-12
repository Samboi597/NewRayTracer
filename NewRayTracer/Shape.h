#pragma once

#include <memory>
#include <vector>
#include "Material.h"
#include "Ray.h"

class Intersections;

using namespace std;

class Shape : public enable_shared_from_this<Shape>
{
protected:
	Matrix transform;
	Material material;

public:
	Shape() : transform(identity(4)) {}

	virtual Point getCenter() const { return Point(0.0f, 0.0f, 0.0f); }
	virtual float getRadius() const { return 1.0f; }

	virtual Vector normalAt(Point const& point) const { return Vector(0.0f, 0.0f, 0.0f); }
	virtual void intersect(Ray const& ray, Intersections &xs) const = 0;

	Matrix getTransform() const { return transform; }
	void setTransform(Matrix const& newTransform) { transform = newTransform; }

	Material getMaterial() const { return material; }
	void setMaterial(Material const& newMaterial) { material = newMaterial; }
};
