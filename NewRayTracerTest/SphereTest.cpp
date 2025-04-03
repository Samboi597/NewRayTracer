#include "pch.h"
#include "CppUnitTest.h"
#include "Ray.h"
#include "Sphere.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SphereTest
{
	TEST_CLASS(SphereTest)
	{
	public:

		TEST_METHOD(TestRayIntersectionWithSphere)
		{
			Ray r(Point(0.0f, 0.0f, -5.0f), Vector(0.0f, 0.0f, 1.0f));
			shared_ptr<Sphere> s = make_shared<Sphere>();
			vector<Intersection> xs;

			s->intersect(r, xs);

			Assert::AreEqual(2, (int)xs.size());
			Assert::AreEqual(4.0f, xs[0].getT(), EPSILON_TEST);
			Assert::AreEqual(6.0f, xs[1].getT(), EPSILON_TEST);

			Assert::IsTrue(s == xs[0].getObject());
			Assert::IsTrue(s == xs[1].getObject());
		}

		TEST_METHOD(TestRayIntersectionWithSphereAtTangent)
		{
			Ray r(Point(0.0f, 1.0f, -5.0f), Vector(0.0f, 0.0f, 1.0f));
			shared_ptr<Sphere> s = make_shared<Sphere>();
			vector<Intersection> xs;

			s->intersect(r, xs);

			Assert::AreEqual(2, (int)xs.size());
			Assert::AreEqual(5.0f, xs[0].getT(), EPSILON_TEST);
			Assert::AreEqual(5.0f, xs[1].getT(), EPSILON_TEST);
		}

		TEST_METHOD(TestRayNotIntersectionWithSphere)
		{
			Ray r(Point(0.0f, 2.0f, -5.0f), Vector(0.0f, 0.0f, 1.0f));
			Sphere s;
			vector<Intersection> xs;

			s.intersect(r, xs);

			Assert::AreEqual(0, (int)xs.size());
		}

		TEST_METHOD(TestRayIntersectionFromInsideSphere)
		{
			Ray r(Point(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 1.0f));
			shared_ptr<Sphere> s = make_shared<Sphere>();
			vector<Intersection> xs;

			s->intersect(r, xs);

			Assert::AreEqual(2, (int)xs.size());
			Assert::AreEqual(-1.0f, xs[0].getT(), EPSILON_TEST);
			Assert::AreEqual(1.0f, xs[1].getT(), EPSILON_TEST);
		}

		TEST_METHOD(TestRayIntersectionBehindSphere)
		{
			Ray r(Point(0.0f, 0.0f, 5.0f), Vector(0.0f, 0.0f, 1.0f));
			shared_ptr<Sphere> s = make_shared<Sphere>();
			vector<Intersection> xs;

			s->intersect(r, xs);

			Assert::AreEqual(2, (int)xs.size());
			Assert::AreEqual(-6.0f, xs[0].getT(), EPSILON_TEST);
			Assert::AreEqual(-4.0f, xs[1].getT(), EPSILON_TEST);
		}

		TEST_METHOD(TestSphereDefaultTransformation)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();

			Assert::IsTrue(identity(4) == s->getTransform());
		}

		TEST_METHOD(TestSphereChangeTransformation)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			Matrix m = translation(2.0f, 3.0f, 4.0f);

			s->setTransform(m);

			Assert::IsTrue(m == s->getTransform());
		}

		TEST_METHOD(TestSphereScaledWithRay)
		{
			Ray r(Point(0.0f, 0.0f, -5.0f), Vector(0.0f, 0.0f, 1.0f));
			shared_ptr<Sphere> s = make_shared<Sphere>();
			Matrix m = scaling(2.0f, 2.0f, 2.0f);

			s->setTransform(m);

			vector<Intersection> xs;

			s->intersect(r, xs);

			Assert::AreEqual(2, (int)xs.size());
			Assert::AreEqual(3.0f, xs[0].getT(), EPSILON_TEST);
			Assert::AreEqual(7.0f, xs[1].getT(), EPSILON_TEST);
		}

		TEST_METHOD(TestSphereTranslatedWithRay)
		{
			Ray r(Point(0.0f, 0.0f, -5.0f), Vector(0.0f, 0.0f, 1.0f));
			shared_ptr<Sphere> s = make_shared<Sphere>();
			Matrix m = translation(5.0f, 0.0f, 0.0f);

			s->setTransform(m);

			vector<Intersection> xs;

			s->intersect(r, xs);

			Assert::AreEqual(0, (int)xs.size());
		}
	};
}