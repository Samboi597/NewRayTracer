#include "Intersection.h"

void Intersection::prepareComputations(Ray const& r)
{
	point = r.position(t);
	eyeV = -r.getDirection();
	normalV = object->normalAt(point);

	if (normalV.dot(eyeV) < 0.0f)
	{
		inside = true;
		normalV = -normalV;
	}
	else
	{
		inside = false;
	}
}
