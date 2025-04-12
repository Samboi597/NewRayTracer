#include <iostream>
#include "Point.h"
#include "Camera.h"
#include "Canvas.h"
#include "Intersections.h"
#include "PointLight.h"
#include "PPMWriter.h"
#include "Scene.h"
#include "Sphere.h"

float const PI = 3.14159265358979323846f;

using namespace std;

int main() {
	PPMWriter writer;
	Scene scene;

	vector<shared_ptr<Shape>> shapes;
	vector<shared_ptr<Light>> lights;

	Material floorMaterial(Colour(1.0f, 0.9f, 0.9f), 0.1f, 0.9f, 0.0f, 200.0f);

	Sphere floor;
	floor.setTransform(scaling(10.0f, 0.01, 10.0f));
	floor.setMaterial(floorMaterial);
	shapes.push_back(make_shared<Sphere>(floor));

	Sphere leftWall;
	leftWall.setTransform(translation(0.0f, 0.0f, 5.0f) * rotationY(-PI / 4) * rotationX(PI / 2) * scaling(10.0f, 0.01f, 10.0f));
	leftWall.setMaterial(floorMaterial);
	shapes.push_back(make_shared<Sphere>(leftWall));

	Sphere rightWall;
	rightWall.setTransform(translation(0.0f, 0.0f, 5.0f) * rotationY(PI / 4) * rotationX(PI / 2) * scaling(10.0f, 0.01f, 10.0f));
	rightWall.setMaterial(floorMaterial);
	shapes.push_back(make_shared<Sphere>(rightWall));

	Sphere middle;
	middle.setTransform(translation(-0.5f, 1.0f, 0.5f));
	middle.setMaterial(Material(Colour(0.1f, 1.0f, 0.5f), 0.1f, 0.7f, 0.3f, 200.0f));
	shapes.push_back(make_shared<Sphere>(middle));

	Sphere right;
	right.setTransform(translation(1.5f, 0.5f, -0.5f) * scaling(0.5f, 0.5f, 0.5f));
	right.setMaterial(Material(Colour(0.5f, 1.0f, 0.1f), 0.1f, 0.7f, 0.3f, 200.0f));
	shapes.push_back(make_shared<Sphere>(right));

	Sphere left;
	left.setTransform(translation(-1.5f, 0.33f, -0.75f) * scaling(0.33f, 0.33f, 0.33f));
	left.setMaterial(Material(Colour(1.0f, 0.8f, 0.1f), 0.1f, 0.7f, 0.3f, 200.0f));
	shapes.push_back(make_shared<Sphere>(left));

	scene.setShapes(shapes);

	PointLight light(Point(-10.0f, 10.0f, -10.0f), Colour(1.0f, 1.0f, 1.0f));
	lights.push_back(make_shared<PointLight>(light));

	scene.setLights(lights);

	Camera camera(100, 50, PI / 3);
	camera.setTransform(viewTransform(Point(0.0f, 1.5f, -5.0f), Point(0.0f, 1.0f, 0.0f), Vector(0.0f, 1.0f, 0.0f)));

	Canvas image = camera.render(scene);

	writer.writeFile("renders/properScene.ppm", image);
}