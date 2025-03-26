#include <iostream>
#include "Point.h"
#include "Canvas.h"
#include "PPMWriter.h"

using namespace std;

struct Projectile {
	Point position;
	Vector velocity;

	// Constructor to initialize position and velocity
	Projectile(Point const& pos, Vector const& vel) : position(pos), velocity(vel) {}
} projectile(Point(0.0f, 1.0f, 0.0f), Vector(1.0f, 1.8f, 0.0f).normalise() * 11.25f);

struct Environment {
	Vector gravity;
	Vector wind;

	// Constructor to initialize gravity and wind
	Environment(Vector const& grav, Vector const& wnd) : gravity(grav), wind(wnd) {}
} environment(Vector(0.0f, -0.1f, 0.0f), Vector(-0.01f, 0.0f, 0.0f));

void tick() {
	projectile.position = projectile.position + projectile.velocity;
	projectile.velocity = projectile.velocity + environment.gravity + environment.wind;
}

int main() {
	Canvas canvas(900, 550);
	PPMWriter writer;

	int numTicks = 0;

	while (projectile.position.getY() > 0.0f) {
		canvas.setPixelColour((int)projectile.position.getX(), canvas.getHeight() - (int)projectile.position.getY(), Colour(1.0f, 0.0f, 0.0f));

		tick();

		numTicks++;

		cout << "Projectile position: (" << projectile.position.getX() << ", " << projectile.position.getY() << ", " << projectile.position.getZ() << ")" << endl;
		cout << "Number of ticks: " << numTicks << endl;
	}

	writer.writeFile("projectile.ppm", canvas);
}