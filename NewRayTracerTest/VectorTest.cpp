#include "pch.h"
#include "CppUnitTest.h"
#include "Vector.cpp"
#include "Point.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VectorTest
{
	TEST_CLASS(VectorTest)
	{
	public:

		TEST_METHOD(TestVectorConstruction)
		{
			Vector vector(4.3f, -4.2f, 3.1f);

			Assert::AreEqual(4.3f, vector.getX(), EPSILON_TEST);
			Assert::AreEqual(-4.2f, vector.getY(), EPSILON_TEST);
			Assert::AreEqual(3.1f, vector.getZ(), EPSILON_TEST);
			Assert::AreEqual(0.0f, vector.getW(), EPSILON_TEST);
		}

		TEST_METHOD(TestVectorAndVectorAddition)
		{
			Vector vector1(4.3f, -4.2f, 3.1f);
			Vector vector2(-2.0f, 3.0f, 1.0f);

			Vector newVector = vector1 + vector2;

			Assert::AreEqual(2.3f, newVector.getX(), EPSILON_TEST);
			Assert::AreEqual(-1.2f, newVector.getY(), EPSILON_TEST);
			Assert::AreEqual(4.1f, newVector.getZ(), EPSILON_TEST);
			Assert::AreEqual(0.0f, newVector.getW(), EPSILON_TEST);
		}

		TEST_METHOD(TestVectorNegation)
		{
			Vector vector(4.3f, -4.2f, 3.1f);

			Vector newVector = -vector;

			Assert::AreEqual(-4.3f, newVector.getX(), EPSILON_TEST);
			Assert::AreEqual(4.2f, newVector.getY(), EPSILON_TEST);
			Assert::AreEqual(-3.1f, newVector.getZ(), EPSILON_TEST);
			Assert::AreEqual(0.0f, newVector.getW(), EPSILON_TEST);
		}

		TEST_METHOD(TestVectorAndVectorSubtractiob)
		{
			Vector vector1(4.3f, -4.2f, 3.1f);
			Vector vector2(-2.0f, 3.0f, 1.0f);

			Vector newVector = vector1 - vector2;

			Assert::AreEqual(6.3f, newVector.getX(), EPSILON_TEST);
			Assert::AreEqual(-7.2f, newVector.getY(), EPSILON_TEST);
			Assert::AreEqual(2.1f, newVector.getZ(), EPSILON_TEST);
			Assert::AreEqual(0.0f, newVector.getW(), EPSILON_TEST);
		}

		TEST_METHOD(TestVectorMultiplication)
		{
			Vector vector(4.3f, -4.2f, 3.1f);

			Vector newVector = vector * 2;

			Assert::AreEqual(8.6f, newVector.getX(), EPSILON_TEST);
			Assert::AreEqual(-8.4f, newVector.getY(), EPSILON_TEST);
			Assert::AreEqual(6.2f, newVector.getZ(), EPSILON_TEST);
			Assert::AreEqual(0.0f, newVector.getW(), EPSILON_TEST);
		}

		TEST_METHOD(TestVectorDivision)
		{
			Vector vector(4.3f, -4.2f, 3.1f);

			Vector newVector = vector / 2;

			Assert::AreEqual(2.15f, newVector.getX(), EPSILON_TEST);
			Assert::AreEqual(-2.1f, newVector.getY(), EPSILON_TEST);
			Assert::AreEqual(1.55f, newVector.getZ(), EPSILON_TEST);
			Assert::AreEqual(0.0f, newVector.getW(), EPSILON_TEST);
		}

		TEST_METHOD(TestVectorMagnitude)
		{
			Vector vector1(1.0f, 0.0f, 0.0f);
			Vector vector2(0.0f, 1.0f, 0.0f);
			Vector vector3(0.0f, 0.0f, 1.0f);
			Vector vector4(1.0f, 2.0f, 3.0f);
			Vector vector5(-1.0f, -2.0f, -3.0f);

			Assert::AreEqual(1.0f, vector1.magnitude(), EPSILON_TEST);
			Assert::AreEqual(1.0f, vector2.magnitude(), EPSILON_TEST);
			Assert::AreEqual(1.0f, vector3.magnitude(), EPSILON_TEST);
			Assert::AreEqual(sqrt(14.0f), vector4.magnitude(), EPSILON_TEST);
			Assert::AreEqual(sqrt(14.0f), vector5.magnitude(), EPSILON_TEST);
		}

		TEST_METHOD(TestVectorNormalise) 
		{
			Vector vector1(4.0f, 0.0f, 0.0f);
			Vector vector2(1.0f, 2.0f, 3.0f);
			Vector vector3(-1.0f, -2.0f, -3.0f);

			Vector nVector1 = vector1.normalise();
			Vector nVector2 = vector2.normalise();
			Vector nVector3 = vector3.normalise();

			Assert::AreEqual(1.0f, nVector1.magnitude(), EPSILON_TEST);
			Assert::AreEqual(1.0f, nVector2.magnitude(), EPSILON_TEST);
			Assert::AreEqual(1.0f, nVector3.magnitude(), EPSILON_TEST);

			Assert::AreEqual(1.0f, nVector1.getX(), EPSILON_TEST);
			Assert::AreEqual(0.0f, nVector1.getY(), EPSILON_TEST);
			Assert::AreEqual(0.0f, nVector1.getZ(), EPSILON_TEST);

			Assert::AreEqual(0.26726f, nVector2.getX(), EPSILON_TEST);
			Assert::AreEqual(0.53452f, nVector2.getY(), EPSILON_TEST);
			Assert::AreEqual(0.80178f, nVector2.getZ(), EPSILON_TEST);

			Assert::AreEqual(-0.26726f, nVector3.getX(), EPSILON_TEST);
			Assert::AreEqual(-0.53452f, nVector3.getY(), EPSILON_TEST);
			Assert::AreEqual(-0.80178f, nVector3.getZ(), EPSILON_TEST);
		}

		TEST_METHOD(TestVectorDotProduct)
		{
			Vector vector1(1.0f, 2.0f, 3.0f);
			Vector vector2(2.0f, 3.0f, 4.0f);
			Assert::AreEqual(20.0f, vector1.dot(vector2), EPSILON_TEST);
		}

		TEST_METHOD(TestVectorCrossProduct)
		{
			Vector vector1(1.0f, 2.0f, 3.0f);
			Vector vector2(2.0f, 3.0f, 4.0f);

			Vector cross1 = vector1.cross(vector2);
			Vector cross2 = vector2.cross(vector1);

			Assert::AreEqual(-1.0f, cross1.getX(), EPSILON_TEST);
			Assert::AreEqual(2.0f, cross1.getY(), EPSILON_TEST);
			Assert::AreEqual(-1.0f, cross1.getZ(), EPSILON_TEST);

			Assert::AreEqual(1.0f, cross2.getX(), EPSILON_TEST);
			Assert::AreEqual(-2.0f, cross2.getY(), EPSILON_TEST);
			Assert::AreEqual(1.0f, cross2.getZ(), EPSILON_TEST);
		}

		TEST_METHOD(TestVectorReflect)
		{
			Vector vector(1.0f, -1.0f, 0.0f);
			Vector normal(0.0f, 1.0f, 0.0f);

			Vector reflected = vector.reflect(normal);

			Assert::AreEqual(1.0f, reflected.getX(), EPSILON_TEST);
			Assert::AreEqual(1.0f, reflected.getY(), EPSILON_TEST);
			Assert::AreEqual(0.0f, reflected.getZ(), EPSILON_TEST);
		}

		TEST_METHOD(TestVectorReflectOffSlantedSurface)
		{
			Vector vector(0.0f, -1.0f, 0.0f);
			Vector normal(sqrt(2.0f) / 2.0f, sqrt(2.0f) / 2.0f, 0.0f);
			Vector reflected = vector.reflect(normal);
			Assert::AreEqual(1.0f, reflected.getX(), EPSILON_TEST);
			Assert::AreEqual(0.0f, reflected.getY(), EPSILON_TEST);
			Assert::AreEqual(0.0f, reflected.getZ(), EPSILON_TEST);
		}
	};
}