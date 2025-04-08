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

		TEST_METHOD(TestSphereNormalAtPointOnXAxis)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			Point p(1.0f, 0.0f, 0.0f);
			Vector expected(1.0f, 0.0f, 0.0f);

			Assert::IsTrue(expected == s->normalAt(p));
		}

		TEST_METHOD(TestSphereNormalAtPointOnYAxis)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			Point p(0.0f, 1.0f, 0.0f);
			Vector expected(0.0f, 1.0f, 0.0f);

			Assert::IsTrue(expected == s->normalAt(p));
		}

		TEST_METHOD(TestSphereNormalAtPointOnZAxis)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			Point p(0.0f, 0.0f, 1.0f);
			Vector expected(0.0f, 0.0f, 1.0f);

			Assert::IsTrue(expected == s->normalAt(p));
		}

		TEST_METHOD(TestSphereNormalAtNonAxialPoint)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			Point p((sqrt(3.0f) / 3.0f), (sqrt(3.0f) / 3.0f), (sqrt(3.0f) / 3.0f));
			Vector expected((sqrt(3.0f) / 3.0f), (sqrt(3.0f) / 3.0f), (sqrt(3.0f) / 3.0f));

			Vector normal = s->normalAt(p);

			Assert::AreEqual(expected.getX(), normal.getX(), EPSILON_TEST);
			Assert::AreEqual(expected.getY(), normal.getY(), EPSILON_TEST);
			Assert::AreEqual(expected.getZ(), normal.getZ(), EPSILON_TEST);
		}

		TEST_METHOD(TestSphereNormalIsNormalised)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			Point p((sqrt(3.0f) / 3.0f), (sqrt(3.0f) / 3.0f), (sqrt(3.0f) / 3.0f));
			Vector expected((sqrt(3.0f) / 3.0f), (sqrt(3.0f) / 3.0f), (sqrt(3.0f) / 3.0f));

			Vector normal = s->normalAt(p);
			expected = expected.normalise();

			Assert::AreEqual(expected.getX(), normal.getX(), EPSILON_TEST);
			Assert::AreEqual(expected.getY(), normal.getY(), EPSILON_TEST);
			Assert::AreEqual(expected.getZ(), normal.getZ(), EPSILON_TEST);
		}

		TEST_METHOD(TestSphereNormalTranslation)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			Matrix m = translation(0.0f, 1.0f, 0.0f);
			
			s->setTransform(m);

			Point p(0.0f, 1.70711f, -0.70711f);
			Vector expected(0.0f, 0.70711f, -0.70711f);

			Vector normal = s->normalAt(p);
			expected = expected.normalise();

			Assert::AreEqual(expected.getX(), normal.getX(), EPSILON_TEST);
			Assert::AreEqual(expected.getY(), normal.getY(), EPSILON_TEST);
			Assert::AreEqual(expected.getZ(), normal.getZ(), EPSILON_TEST);
		}

		TEST_METHOD(TestSphereNormalTransformation)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			Matrix m = scaling(1.0f, 0.5f, 1.0f);
			Point p(0.0f, sqrt(2.0f), -sqrt(2.0f));
			Vector expected(0.0f, 0.70711f, -0.70711f);

			m = rotationZ(PI / 5.0f);
			s->setTransform(m);
			Vector normal = s->normalAt(p);

			expected = expected.normalise();
			Assert::AreEqual(expected.getX(), normal.getX(), EPSILON_TEST);
			Assert::AreEqual(expected.getY(), normal.getY(), EPSILON_TEST);
			Assert::AreEqual(expected.getZ(), normal.getZ(), EPSILON_TEST);
		}

		TEST_METHOD(TestSphereDefaultMaterial)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();

			Material m = s->getMaterial();

			Assert::AreEqual(1.0f, m.getColour().getR(), EPSILON_TEST);
			Assert::AreEqual(1.0f, m.getColour().getG(), EPSILON_TEST);
			Assert::AreEqual(1.0f, m.getColour().getB(), EPSILON_TEST);

			Assert::AreEqual(0.1f, m.getAmbient(), EPSILON_TEST);
			Assert::AreEqual(0.9f, m.getDiffuse(), EPSILON_TEST);
			Assert::AreEqual(0.9f, m.getSpecular(), EPSILON_TEST);
			Assert::AreEqual(200.0f, m.getShininess(), EPSILON_TEST);
		}

		TEST_METHOD(TestSphereAssignedMaterial)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();

			Material m;
			m.setAmbient(1.0f);
			m.setDiffuse(1.0f);
			m.setSpecular(1.0f);
			m.setShininess(1.0f);
			s->setMaterial(m);

			Assert::AreEqual(1.0f, s->getMaterial().getAmbient(), EPSILON_TEST);
			Assert::AreEqual(1.0f, s->getMaterial().getDiffuse(), EPSILON_TEST);
			Assert::AreEqual(1.0f, s->getMaterial().getSpecular(), EPSILON_TEST);
			Assert::AreEqual(1.0f, s->getMaterial().getShininess(), EPSILON_TEST);
		}
	};
}