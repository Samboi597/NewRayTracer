#include "Sphere.h"

void Sphere::intersect(Ray const& ray, Intersections &xs) const
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

Vector Sphere::normalAt(Point const& point) const
{
	Vector objectPoint = getTransform().inverse() * point;

	Vector objectNormal = objectPoint - center;

	Vector worldNormal = getTransform().inverse().transpose() * objectNormal;
	worldNormal.setW(0.0f);

	return worldNormal.normalise();
}
