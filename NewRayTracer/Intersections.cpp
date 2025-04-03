#include "Intersections.h"

Intersection const Intersections::getHit()
{
	Intersection result;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].getT() >= 0.0f)
		{
			if (!result.has_value() || data[i].getT() < result.getT())
			{
				result = data[i];
			}
		}
	}
	return result;
}