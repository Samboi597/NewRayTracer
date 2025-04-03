#include "pch.h"
#include "CppUnitTest.h"
#include "Intersections.cpp"
#include "Sphere.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntersectionsTest
{
	TEST_CLASS(IntersectionsTest)
	{
	public:

		TEST_METHOD(TestRayIntersectionIncludingSphere)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			Intersection i(3.5f, s);

			Assert::AreEqual(3.5f, i.getT(), EPSILON_TEST);
			Assert::IsTrue(Point(0.0f, 0.0f, 0.0f) == i.getObject()->getCenter());
			Assert::AreEqual(1.0f, i.getObject()->getRadius(), EPSILON_TEST);
		}

		TEST_METHOD(TesRayIntersectionsAggregation)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			vector<Intersection> iVec;

			iVec.push_back(Intersection(1.0f, s));
			iVec.push_back(Intersection(2.0f, s));

			Intersections xs(iVec);

			Assert::AreEqual(2, xs.getCount());
			Assert::AreEqual(1.0f, xs.getIntersection(0).getT(), EPSILON_TEST);
			Assert::AreEqual(2.0f, xs.getIntersection(1).getT(), EPSILON_TEST);
		}

		TEST_METHOD(TestRayIntersectionsHitAllTValuesPositive)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			vector<Intersection> iVec;

			iVec.push_back(Intersection(1.0f, s));
			iVec.push_back(Intersection(2.0f, s));

			Intersections xs(iVec);

			Assert::IsTrue(xs.getHit().has_value());
			Assert::AreEqual(1.0f, xs.getHit().getT(), EPSILON_TEST);
		}

		TEST_METHOD(TestRayIntersectionsHitSomeTValuesNegative)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			vector<Intersection> iVec;

			iVec.push_back(Intersection(-1.0f, s));
			iVec.push_back(Intersection(1.0f, s));

			Intersections xs(iVec);

			Assert::IsTrue(xs.getHit().has_value());
			Assert::AreEqual(1.0f, xs.getHit().getT(), EPSILON_TEST);
		}

		TEST_METHOD(TestRayIntersectionsHitAllTValuesNegative)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			vector<Intersection> iVec;

			iVec.push_back(Intersection(-2.0f, s));
			iVec.push_back(Intersection(-1.0f, s));

			Intersections xs(iVec);

			Assert::IsFalse(xs.getHit().has_value());
		}

		TEST_METHOD(TestRayIntersectionsHitLowestNonNegativeValue)
		{
			shared_ptr<Sphere> s = make_shared<Sphere>();
			vector<Intersection> iVec;

			iVec.push_back(Intersection(5.0f, s));
			iVec.push_back(Intersection(7.0f, s));
			iVec.push_back(Intersection(-3.0f, s));
			iVec.push_back(Intersection(2.0f, s));

			Intersections xs(iVec);

			Assert::IsTrue(xs.getHit().has_value());
			Assert::AreEqual(2.0f, xs.getHit().getT(), EPSILON_TEST);
		}
	};
}