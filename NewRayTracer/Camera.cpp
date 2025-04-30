#include "Camera.h"

Ray Camera::rayForPixel(float const& x, float const& y) const {
	float xOffset = x * pixelSize;
	float yOffset = y * pixelSize;

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
			Ray rayCenter = rayForPixel(((float)x + 0.5f), ((float)y + 0.5f));
			Colour colour = scene.colourAt(rayCenter) / 2.0f;

			for (int i = 0; i <= 1; i++) {
				for (int j = 0; j <= 1; j++) {
					Ray ray = rayForPixel(((float)x + (float)i), ((float)y + (float)j));
					colour = colour + (scene.colourAt(ray) / 8.0f);
				}
			}

			image.setPixelColour(x, y, colour);
		}
	}

	return image;
}
