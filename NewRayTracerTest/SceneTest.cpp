#include "pch.h"
#include "CppUnitTest.h"
#include "Scene.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SceneTest
{
	TEST_CLASS(SceneTest)
	{
	public:

		TEST_METHOD(TestSceneDefault)
		{
			Scene scene;

			Assert::AreEqual(1, (int)(scene.getLights().size()));

			Assert::IsTrue(Point(-10.0f, 10.0f, -10.0f) == scene.getLights()[0]->getPosition());
			Assert::IsTrue(Colour(1.0f, 1.0f, 1.0f) == scene.getLights()[0]->getIntensity());

			Assert::AreEqual(2, (int)(scene.getShapes().size()));

			Assert::IsTrue(Point(0.0f, 0.0f, 0.0f) == scene.getShapes()[0]->getCenter());
			Assert::AreEqual(1.0f, scene.getShapes()[0]->getRadius());
			Assert::IsTrue(Colour(0.8f, 1.0f, 0.6f) == scene.getShapes()[0]->getMaterial().getColour());
			Assert::AreEqual(0.1f, scene.getShapes()[0]->getMaterial().getAmbient(), EPSILON_TEST);
			Assert::AreEqual(0.7f, scene.getShapes()[0]->getMaterial().getDiffuse(), EPSILON_TEST);
			Assert::AreEqual(0.2f, scene.getShapes()[0]->getMaterial().getSpecular(), EPSILON_TEST);
			Assert::AreEqual(200.0f, scene.getShapes()[0]->getMaterial().getShininess(), EPSILON_TEST);

			Assert::IsTrue(Point(0.0f, 0.0f, 0.0f) == scene.getShapes()[1]->getCenter());
			Assert::AreEqual(1.0f, scene.getShapes()[1]->getRadius());
			Assert::IsTrue(scaling(0.5f, 0.5f, 0.5f) == scene.getShapes()[1]->getTransform());
		}

		TEST_METHOD(TestSceneIntersectWithRay)
		{
			Scene scene;
			Ray r(Point(0.0f, 0.0f, -5.0f), Vector(0.0f, 0.0f, 1.0f));
			Intersections xs;

			xs = scene.intersectScene(r);

			Assert::AreEqual(4, xs.getCount());
			Assert::AreEqual(4.0f, xs.getIntersection(0).getT(), EPSILON_TEST);
			Assert::AreEqual(4.5f, xs.getIntersection(1).getT(), EPSILON_TEST);
			Assert::AreEqual(5.5f, xs.getIntersection(2).getT(), EPSILON_TEST);
			Assert::AreEqual(6.0f, xs.getIntersection(3).getT(), EPSILON_TEST);
		}

		TEST_METHOD(TestSceneShadingIntersection)
		{
			Scene scene;
			Ray r(Point(0.0f, 0.0f, -5.0f), Vector(0.0f, 0.0f, 1.0f));
			shared_ptr<Shape> s = scene.getShapes()[0];
			Intersection i(4.0f, s);

			i.prepareComputations(r);
			Colour c = scene.shadeHit(i);

			Assert::AreEqual(0.38066f, c.getR(), EPSILON_TEST);
			Assert::AreEqual(0.47583f, c.getG(), EPSILON_TEST);
			Assert::AreEqual(0.2855f, c.getB(), EPSILON_TEST);
		}

		TEST_METHOD(TestSceneShadingIntersectionFromInside)
		{
			Scene scene;

			vector<shared_ptr<Light>> lights;
			lights.push_back(make_shared<PointLight>(Point(0.0f, 0.25f, 0.0f), Colour(1.0f, 1.0f, 1.0f)));
			scene.setLights(lights);

			Ray r(Point(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 1.0f));
			shared_ptr<Shape> s = scene.getShapes()[1];
			Intersection i(0.5f, s);

			i.prepareComputations(r);
			Colour c = scene.shadeHit(i);

			Assert::AreEqual(0.90498f, c.getR(), EPSILON_TEST);
			Assert::AreEqual(0.90498f, c.getG(), EPSILON_TEST);
			Assert::AreEqual(0.90498f, c.getB(), EPSILON_TEST);
		}

		TEST_METHOD(TestSceneColourWhenRayMisses)
		{
			Scene scene;
			Ray r(Point(0.0f, 0.0f, -5.0f), Vector(0.0f, 1.0f, 0.0f));

			Colour c = scene.colourAt(r);

			Assert::IsTrue(Colour(0.0f, 0.0f, 0.0f) == c);
		}

		TEST_METHOD(TestSceneColourWhenRayHits)
		{
			Scene scene;
			Ray r(Point(0.0f, 0.0f, -5.0f), Vector(0.0f, 0.0f, 1.0f));

			Colour c = scene.colourAt(r);

			Assert::AreEqual(0.38066f, c.getR(), EPSILON_TEST);
			Assert::AreEqual(0.47583f, c.getG(), EPSILON_TEST);
			Assert::AreEqual(0.2855f, c.getB(), EPSILON_TEST);
		}

		TEST_METHOD(TestSceneColourWithIntersectionBehindRay)
		{
			Scene scene;

			Material m1 = scene.getShapes()[0]->getMaterial();
			m1.setAmbient(1.0f);
			scene.getShapes()[0]->setMaterial(m1);

			Material m2 = scene.getShapes()[1]->getMaterial();
			m2.setAmbient(1.0f);
			scene.getShapes()[1]->setMaterial(m2);

			Ray r(Point(0.0f, 0.0f, 0.75f), Vector(0.0f, 0.0f, -1.0f));

			Colour cActual = scene.colourAt(r);
			Colour cExpected = scene.getShapes()[1]->getMaterial().getColour();

			Assert::IsTrue(cExpected == cActual);
		}
	};
}