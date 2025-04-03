#include "Sphere.h"

void Sphere::intersect(Ray const& ray, vector<Intersection>& xs) const
{
	Ray transformedRay = ray.transform(getTransform().inverse());

	Vector sphereToRay = transformedRay.getOrigin() - center;

	float a = transformedRay.getDirection().dot(transformedRay.getDirection());
	float b = 2.0f * transformedRay.getDirection().dot(sphereToRay);
	float c = sphereToRay.dot(sphereToRay) - 1.0f;

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant >= 0.0f)
	{
		float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
		float t2 = (-b + sqrt(discriminant)) / (2.0f * a);

		xs.push_back(Intersection(t1, shared_from_this()));
		xs.push_back(Intersection(t2, shared_from_this()));
	}
}