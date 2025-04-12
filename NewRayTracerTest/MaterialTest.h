#include "pch.h"
#include "CppUnitTest.h"
#include "Material.cpp"
#include "PointLight.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MaterialTest
{
	TEST_CLASS(MaterialTest)
	{
	public:

		TEST_METHOD(TestMaterialConstruction)
		{
			Material material;

			Assert::IsTrue(material.getColour() == Colour(1.0f, 1.0f, 1.0f));
			Assert::AreEqual(0.1f, material.getAmbient(), EPSILON_TEST);
			Assert::AreEqual(0.9f, material.getDiffuse(), EPSILON_TEST);
			Assert::AreEqual(0.9f, material.getSpecular(), EPSILON_TEST);
			Assert::AreEqual(200.0f, material.getShininess(), EPSILON_TEST);
		}

		TEST_METHOD(TestMaterialLightingEyeBetweenLightAndSurface)
		{
			Material material;

			Point position(0.0f, 0.0f, 0.0f);
			Vector eyeV(0.0f, 0.0f, -1.0f);
			Vector normalV(0.0f, 0.0f, -1.0f);
			PointLight light(Point(0.0f, 0.0f, -10.0f), Colour(1.0f, 1.0f, 1.0f));

			Colour result = material.lighting(light.getPosition(), light.getIntensity(), position, eyeV, normalV);

			Assert::IsTrue(result == Colour(1.9f, 1.9f, 1.9f));
		}

		TEST_METHOD(TestMaterialLightingEyeBetweenLightAndSurfaceEye45DegreesOffset)
		{
			Material material;

			Point position(0.0f, 0.0f, 0.0f);
			Vector eyeV(0.0f, sqrt(2.0f) / 2.0f, -sqrt(2.0f) / 2.0f);
			Vector normalV(0.0f, 0.0f, -1.0f);
			PointLight light(Point(0.0f, 0.0f, -10.0f), Colour(1.0f, 1.0f, 1.0f));

			Colour result = material.lighting(light.getPosition(), light.getIntensity(), position, eyeV, normalV);
			
			Assert::IsTrue(result == Colour(1.0f, 1.0f, 1.0f));
		}

		TEST_METHOD(TestMaterialLightingEyeOppositeSurfaceLight45DegreesOffset)
		{
			Material material;

			Point position(0.0f, 0.0f, 0.0f);
			Vector eyeV(0.0f, 0.0f, -1.0f);
			Vector normalV(0.0f, 0.0f, -1.0f);
			PointLight light(Point(0.0f, 10.0f, -10.0f), Colour(1.0f, 1.0f, 1.0f));

			Colour result = material.lighting(light.getPosition(), light.getIntensity(), position, eyeV, normalV);
			Assert::AreEqual(0.7364f, result.getR(), EPSILON_TEST);
			Assert::AreEqual(0.7364f, result.getG(), EPSILON_TEST);
			Assert::AreEqual(0.7364f, result.getB(), EPSILON_TEST);
		}

		TEST_METHOD(TestMaterialLightingEyeInPathOfReflectionVector)
		{
			Material material;

			Point position(0.0f, 0.0f, 0.0f);
			Vector eyeV(0.0f, -sqrt(2.0f) / 2.0f, -sqrt(2.0f) / 2.0f);
			Vector normalV(0.0f, 0.0f, -1.0f);
			PointLight light(Point(0.0f, 10.0f, -10.0f), Colour(1.0f, 1.0f, 1.0f));

			Colour result = material.lighting(light.getPosition(), light.getIntensity(), position, eyeV, normalV);
			Assert::AreEqual(1.63639f, result.getR(), EPSILON_TEST);
			Assert::AreEqual(1.63639f, result.getG(), EPSILON_TEST);
			Assert::AreEqual(1.63639f, result.getB(), EPSILON_TEST);
		}

		TEST_METHOD(TestMaterialLightingLightBehindSurface)
		{
			Material material;

			Point position(0.0f, 0.0f, 0.0f);
			Vector eyeV(0.0f, 0.0f, -1.0f);
			Vector normalV(0.0f, 0.0f, -1.0f);
			PointLight light(Point(0.0f, 0.0f, 10.0f), Colour(1.0f, 1.0f, 1.0f));

			Colour result = material.lighting(light.getPosition(), light.getIntensity(), position, eyeV, normalV);
			
			Assert::IsTrue(result == Colour(0.1f, 0.1f, 0.1f));
		}
	};
}