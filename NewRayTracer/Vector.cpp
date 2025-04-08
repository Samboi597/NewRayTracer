#include "Vector.h"

Vector Vector::reflect(Vector const& normal) const
{
	float dotProduct = dot(normal);

    return Vector(x - normal.getX() * 2.0f * dotProduct, y - normal.getY() * 2.0f * dotProduct, z - normal.getZ() * 2.0f * dotProduct);
}
