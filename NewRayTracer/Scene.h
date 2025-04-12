#pragma once

#include "Light.h"
#include "Sphere.h"

class Intersections;

class Scene
{
private:
	vector<shared_ptr<Light>> lights;
	vector<shared_ptr<Shape>> shapes;

public:
	Scene();
	Scene(vector<shared_ptr<Light>> const& newLights, vector<shared_ptr<Shape>> const& newShapes)
		: lights(newLights), shapes(newShapes) {
	}

	vector<shared_ptr<Light>> getLights() const { return lights; }
	vector<shared_ptr<Shape>> getShapes() const { return shapes; }

	void setLights(vector<shared_ptr<Light>> const& newLights) { lights = newLights; }
	void setShapes(vector<shared_ptr<Shape>> const& newShapes) { shapes = newShapes; }

	Intersections intersectScene(Ray const& ray) const;
	Colour shadeHit(Intersection const& i) const;
	Colour colourAt(Ray const& ray) const;
};