#pragma once

#include "Canvas.h"
#include "Matrix.h"
#include "Ray.h"
#include "Scene.h"

class Camera
{
private:
	int hSize;
	int vSize;
	float fieldOfView;
	Matrix transform;

	float halfWidth;
	float halfHeight;
	float pixelSize;

public:
	Camera(int const& newHSize, int const& newVSize, float const& newFieldOfView) : hSize(newHSize), vSize(newVSize), fieldOfView(newFieldOfView), transform(identity(4)) {
		float halfView = tan(fieldOfView / 2.0f);
		float aspect = (float)hSize / (float)vSize;

		if (aspect >= 1.0f) {
			halfWidth = halfView;
			halfHeight = halfView / aspect;
		}
		else {
			halfWidth = halfView * aspect;
			halfHeight = halfView;
		}

		pixelSize = (halfWidth * 2.0f) / (float)hSize;
	}

	int getWidth() const { return hSize; }
	int getHeight() const { return vSize; }
	float getFieldOfView() const { return fieldOfView; }
	Matrix getTransform() const { return transform; }
	float getPixelSize() const { return pixelSize; }

	void setTransform(Matrix const& newTransform) { transform = newTransform; }

	Ray rayForPixel(int const& x, int const& y) const;
	Canvas render(Scene const& scene) const;
};
