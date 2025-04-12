#include "Camera.h"

Ray Camera::rayForPixel(int const& x, int const& y) const {
	float xOffset = ((float)x + 0.5f) * pixelSize;
	float yOffset = ((float)y + 0.5f) * pixelSize;

	float worldX = halfWidth - xOffset;
	float worldY = halfHeight - yOffset;

	Point pixel = transform.inverse() * Point(worldX, worldY, -1.0f);
	Point origin = transform.inverse() * Point(0, 0, 0);
	Vector direction = (pixel - origin).normalise();

	return Ray(origin, direction);
}

Canvas Camera::render(Scene const& scene) const
{
	Canvas image(hSize, vSize);

	for (int y = 0; y < vSize; y++) {
		for (int x = 0; x < hSize; x++) {
			Ray ray = rayForPixel(x, y);
			Colour colour = scene.colourAt(ray);
			image.setPixelColour(x, y, colour);
		}
	}

	return image;
}
