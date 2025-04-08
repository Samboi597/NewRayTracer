#include <iostream>
#include "Point.h"
#include "Canvas.h"
#include "Intersections.h"
#include "PointLight.h"
#include "PPMWriter.h"
#include "Sphere.h"

float const PI = 3.14159265358979323846f;

using namespace std;

int main() {
	Canvas canvas(400, 400);
	PPMWriter writer;

	float pixelSize = 7.0f / canvas.getWidth();
	float half = 3.5f;

	shared_ptr<Sphere> sphere = make_shared<Sphere>();
	sphere->setMaterial(Material(Colour(1.0f, 0.2f, 1.0f), 0.1f, 0.9f, 0.9f, 200.0f));

	Point lightPosition(-10.0f, 10.0f, -10.0f);
	Colour lightIntensity(1.0f, 1.0f, 1.0f);
	PointLight light(lightPosition, lightIntensity);

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
				Intersection hit = xs.getHit();
				Point hitPoint = ray.position(hit.getT());
				Vector normal = sphere->normalAt(hitPoint);
				Vector eye = -ray.getDirection();

				Colour colour = sphere->getMaterial().lighting(light.getPosition(), light.getIntensity(), hitPoint, eye, normal);

				std::cout << "Drawing pixel colour (" << colour.getR() << ", " << colour.getG() << ", " << colour.getB() << ") at (" << x << ", " << y << ")" << std::endl;

				canvas.setPixelColour(x, y, colour);
			}
		}
	}

	writer.writeFile("sphereWithLighting.ppm", canvas);
}