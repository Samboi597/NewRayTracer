#include <iostream>
#include "Point.h"
#include "Canvas.h"
#include "PPMWriter.h"

float const PI = 3.14159265358979323846f;

using namespace std;

int main() {
	Canvas canvas(900, 550);
	PPMWriter writer;

	Point origin(450.0f, 0.0f, 275.0f);
	float radius = 225.0f;

	for (int i = 0; i < 12; i++) {
		float radians = i * PI / 6.0f;

		float x = origin.getX() + radius * cos(radians);
		float y = origin.getZ() + radius * sin(radians);

		canvas.setPixelColour((int)x, (int)y, Colour(1.0f, 1.0f, 1.0f));
	}

	writer.writeFile("clock.ppm", canvas);
}