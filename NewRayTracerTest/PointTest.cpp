#include "pch.h"
#include "CppUnitTest.h"
#include "Point.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PointTest
{
	TEST_CLASS(PointTest)
	{
	public:

		TEST_METHOD(TestPointConstruction)
		{
			Point point(4.3f, -4.2f, 3.1f);

			Assert::AreEqual(4.3f, point.getX(), EPSILON_TEST);
			Assert::AreEqual(-4.2f, point.getY(), EPSILON_TEST);
			Assert::AreEqual(3.1f, point.getZ(), EPSILON_TEST);
			Assert::AreEqual(1.0f, point.getW(), EPSILON_TEST);
		}

		TEST_METHOD(TestPointAndVectorAddition)
		{
			Point point(4.3f, -4.2f, 3.1f);
			Vector vector(-2.0f, 3.0f, 1.0f);

			Point newPoint = point + vector;

			Assert::AreEqual(2.3f, newPoint.getX(), EPSILON_TEST);
			Assert::AreEqual(-1.2f, newPoint.getY(), EPSILON_TEST);
			Assert::AreEqual(4.1f, newPoint.getZ(), EPSILON_TEST);
			Assert::AreEqual(1.0f, newPoint.getW(), EPSILON_TEST);
		}

		TEST_METHOD(TestPointAndVectorSubtraction)
		{
			Point point(4.3f, -4.2f, 3.1f);
			Vector vector(-2.0f, 3.0f, 1.0f);

			Point newPoint = point - vector;

			Assert::AreEqual(6.3f, newPoint.getX(), EPSILON_TEST);
			Assert::AreEqual(-7.2f, newPoint.getY(), EPSILON_TEST);
			Assert::AreEqual(2.1f, newPoint.getZ(), EPSILON_TEST);
			Assert::AreEqual(1.0f, newPoint.getW(), EPSILON_TEST);
		}

		TEST_METHOD(TestPointAndPointSubtraction)
		{
			Point point1(4.3f, -4.2f, 3.1f);
			Point point2(-2.0f, 3.0f, 1.0f);

			Vector newVector = point1 - point2;

			Assert::AreEqual(6.3f, newVector.getX(), EPSILON_TEST);
			Assert::AreEqual(-7.2f, newVector.getY(), EPSILON_TEST);
			Assert::AreEqual(2.1f, newVector.getZ(), EPSILON_TEST);
			Assert::AreEqual(0.0f, newVector.getW(), EPSILON_TEST);
		}
	};
}