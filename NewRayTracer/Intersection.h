#pragma once

#include "Shape.h"
#include <memory>

using namespace std;

class Intersection
{
private:
	float t;
	shared_ptr<Shape const> object;

public:
	Intersection() : t(0.0f), object(nullptr) {}
	Intersection(float const& newT, shared_ptr<Shape const> const& newObject) : t(newT), object(newObject) {}
	
	float getT() const { return t; }
	shared_ptr<Shape const> getObject() const { return object; }
	bool has_value() const { return object != nullptr; }
};
