#include "Scene.h"

#include "PointLight.h"

Scene::Scene()
{
	lights.push_back(make_shared<PointLight>(Point(-10.0f, 10.0f, -10.0f), Colour(1.0f, 1.0f, 1.0f)));

	Sphere s1, s2;
	Material m;

	m.setColour(Colour(0.8f, 1.0f, 0.6f));
	m.setDiffuse(0.7f);
	m.setSpecular(0.2f);

	s1.setMaterial(m);

	s2.setTransform(scaling(0.5f, 0.5f, 0.5f));

	shapes.push_back(make_shared<Sphere>(s1));
	shapes.push_back(make_shared<Sphere>(s2));
}

Intersections Scene::intersectScene(Ray const& ray) const
{
	Intersections xs;

	for (auto shape = shapes.begin(); shape != shapes.end(); ++shape) {
		shape->get()->intersect(ray, xs);
	}

	xs.sortData();
	return xs;
}

Colour Scene::shadeHit(Intersection const& i) const
{
	Colour c;

	for (auto light = lights.begin(); light != lights.end(); ++light) {
		c = c + i.getObject()->getMaterial().lighting((*light)->getPosition(), (*light)->getIntensity(), i.getPoint(), i.getEyeV(), i.getNormalV());
	}

	return c;
}

Colour Scene::colourAt(Ray const& ray) const
{
	Intersections xs = intersectScene(ray);

	Intersection hit = xs.getHit();
	if (!hit.has_value()) {
		return Colour(0.0f, 0.0f, 0.0f);
	}

	hit.prepareComputations(ray);

	return shadeHit(hit);
}
