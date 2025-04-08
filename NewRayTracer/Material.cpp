#include "Material.h"

Colour Material::lighting(Point const& lightPosition, Colour const& lightIntensity, Point const& point, Vector const& eyeVector, Vector const& normalVector) const
{
    Colour effectiveColour = materialColour * lightIntensity;
    Vector lightVector = (lightPosition - point).normalise();

	Colour ambient = effectiveColour * materialAmbient, diffuse, specular;
	float lightDotNormal = lightVector.dot(normalVector);

	if (lightDotNormal >= 0.0f) {
		diffuse = effectiveColour * materialDiffuse * lightDotNormal;

		Vector reflectVector = -lightVector.reflect(normalVector);
		float reflectDotEye = reflectVector.dot(eyeVector);

		if (reflectDotEye > 0.0f) {
			float factor = pow(reflectDotEye, materialShininess);

			specular = lightIntensity * materialSpecular * factor;
		}
	}

    return ambient + diffuse + specular;
}
