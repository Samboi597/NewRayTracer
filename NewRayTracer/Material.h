#pragma once

#include "Colour.h"
#include "Point.h"

class Material
{
private:
	Colour materialColour;
	float materialAmbient;
	float materialDiffuse;
	float materialSpecular;
	float materialShininess;

public:
	Material()
		: materialColour(Colour(1.0f, 1.0f, 1.0f)), materialAmbient(0.1f), materialDiffuse(0.9f), materialSpecular(0.9f), materialShininess(200.0f) {
	}
	Material(Colour const& newColour, float newAmbient, float newDiffuse, float newSpecular, float newShininess)
		: materialColour(newColour), materialAmbient(newAmbient), materialDiffuse(newDiffuse), materialSpecular(newSpecular), materialShininess(newShininess) {
	}

	Colour lighting(Point const &lightPosition, Colour const &lightIntensity, Point const &point, Vector const &eyeVector, Vector const &normalVector) const;

	Colour getColour() const { return materialColour; }
	float getAmbient() const { return materialAmbient; }
	float getDiffuse() const { return materialDiffuse; }
	float getSpecular() const { return materialSpecular; }
	float getShininess() const { return materialShininess; }

	void setColour(Colour const& newColour) { materialColour = newColour; }
	void setAmbient(float newAmbient) { materialAmbient = newAmbient; }
	void setDiffuse(float newDiffuse) { materialDiffuse = newDiffuse; }
	void setSpecular(float newSpecular) { materialSpecular = newSpecular; }
	void setShininess(float newShininess) { materialShininess = newShininess; }
};
