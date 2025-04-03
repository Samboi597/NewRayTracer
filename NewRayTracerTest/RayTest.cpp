#include "pch.h"
#include "CppUnitTest.h"
#include "Ray.h"
#include "Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RayTest
{
	TEST_CLASS(RayTest)
	{
	public:
		TEST_METHOD(TestRayConstructor)
		{
			Point origin(1.0f, 2.0f, 3.0f);
			Vector direction(4.0f, 5.0f, 6.0f);

			Ray r(origin, direction);

			Assert::IsTrue(origin == r.getOrigin());
			Assert::IsTrue(direction == r.getDirection());
		}

		TEST_METHOD(TestRayPosition)
		{
			Ray r(Point(2.0f, 3.0f, 4.0f), Vector(1.0f, 0.0f, 0.0f));

			Assert::IsTrue(Point(2.0f, 3.0f, 4.0f) == r.position(0.0f));
			Assert::IsTrue(Point(3.0f, 3.0f, 4.0f) == r.position(1.0f));
			Assert::IsTrue(Point(1.0f, 3.0f, 4.0f) == r.position(-1.0f));
			Assert::IsTrue(Point(4.5f, 3.0f, 4.0f) == r.position(2.5f));
		}

		TEST_METHOD(TestRayTranslation)
		{
			Ray r(Point(1.0f, 2.0f, 3.0f), Vector(0.0f, 1.0f, 0.0f));
			Matrix m = translation(3.0f, 4.0f, 5.0f);

			Ray r2 = r.transform(m);

			Assert::IsTrue(Point(4.0f, 6.0f, 8.0f) == r2.getOrigin());
			Assert::IsTrue(Vector(0.0f, 1.0f, 0.0f) == r2.getDirection());
		}

		TEST_METHOD(TestRayScaling)
		{
			Ray r(Point(1.0f, 2.0f, 3.0f), Vector(0.0f, 1.0f, 0.0f));
			Matrix m = scaling(2.0f, 3.0f, 4.0f);

			Ray r2 = r.transform(m);

			Assert::IsTrue(Point(2.0f, 6.0f, 12.0f) == r2.getOrigin());
			Assert::IsTrue(Vector(0.0f, 3.0f, 0.0f) == r2.getDirection());
		}
	};
}