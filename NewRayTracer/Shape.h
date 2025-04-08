#pragma once

#include <memory>
#include "Point.h"
#include "Matrix.h"
#include "Material.h"

using namespace std;

class Shape : public enable_shared_from_this<Shape>
{
protected:
	Matrix transform;
	Material material;

public:
	Shape() : transform(identity(4)) {}

	virtual Point getCenter() const = 0;
	virtual float getRadius() const = 0;

	virtual Vector normalAt(Point const& point) const = 0;

	Matrix getTransform() const { return transform; }
	void setTransform(Matrix const& newTransform) { transform = newTransform; }

	Material getMaterial() const { return material; }
	void setMaterial(Material const& newMaterial) { material = newMaterial; }
};
