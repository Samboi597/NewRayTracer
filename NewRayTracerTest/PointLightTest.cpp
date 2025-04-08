#include "pch.h"
#include "CppUnitTest.h"
#include "PointLight.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PointLightTest
{
	TEST_CLASS(PointLightTest)
	{
	public:

		TEST_METHOD(TestPointLightConstruction)
		{
			Colour intensity(1.0f, 1.0f, 1.0f);
			Point position(0.0f, 0.0f, 0.0f);

			PointLight light(position, intensity);

			Assert::AreEqual(1.0f, light.getIntensity().getR(), EPSILON_TEST);
			Assert::AreEqual(1.0f, light.getIntensity().getG(), EPSILON_TEST);
			Assert::AreEqual(1.0f, light.getIntensity().getB(), EPSILON_TEST);

			Assert::AreEqual(0.0f, light.getPosition().getX(), EPSILON_TEST);
			Assert::AreEqual(0.0f, light.getPosition().getY(), EPSILON_TEST);
			Assert::AreEqual(0.0f, light.getPosition().getZ(), EPSILON_TEST);
		}
	};
}