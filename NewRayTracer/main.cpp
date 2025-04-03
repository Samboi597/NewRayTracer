#include <iostream>
#include "Point.h"
#include "Canvas.h"
#include "Intersections.h"
#include "PPMWriter.h"
#include "Sphere.h"

float const PI = 3.14159265358979323846f;

using namespace std;

int main() {
	Canvas canvas(100, 100);
	PPMWriter writer;

	float pixelSize = 7.0f / canvas.getWidth();
	float half = 3.5f;

	shared_ptr<Sphere> sphere = make_shared<Sphere>();
	Colour sphereColour(1.0f, 0.0f, 0.0f);

	Point origin(0.0f, 0.0f, -5.0f);

	for (int y = 0; y < canvas.getHeight(); y++) {
		float worldY = half - pixelSize * y;

		for (int x = 0; x < canvas.getWidth(); x++) {
			float worldX = -half + pixelSize * x;
			
			Point point(worldX, worldY, 10.0f);

			Ray ray(origin, Vector(point - origin).normalise());

			vector<Intersection> iVec;

			sphere->intersect(ray, iVec);

			Intersections xs(iVec);

			if (xs.getHit().getT() > 0.0f) {
				canvas.setPixelColour(x, y, sphereColour);
			}
		}
	}

	writer.writeFile("sphere.ppm", canvas);
}