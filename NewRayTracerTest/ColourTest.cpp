#include "pch.h"
#include "CppUnitTest.h"
#include "Colour.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ColourTest
{
	TEST_CLASS(ColourTest)
	{
	public:

		TEST_METHOD(TestColourConstruction)
		{
			Colour colour(-0.5f, 0.4f, 1.7f);

			Assert::AreEqual(-0.5f, colour.getR(), EPSILON_TEST);
			Assert::AreEqual(0.4f, colour.getG(), EPSILON_TEST);
			Assert::AreEqual(1.7f, colour.getB(), EPSILON_TEST);
		}

		TEST_METHOD(TestColourAddition)
		{
			Colour colour1(0.9f, 0.6f, 0.75f);
			Colour colour2(0.7f, 0.1f, 0.25f);

			Colour newColour = colour1 + colour2;

			Assert::AreEqual(1.6f, newColour.getR(), EPSILON_TEST);
			Assert::AreEqual(0.7f, newColour.getG(), EPSILON_TEST);
			Assert::AreEqual(1.0f, newColour.getB(), EPSILON_TEST);
		}

		TEST_METHOD(TestColourSubtraction)
		{
			Colour colour1(0.9f, 0.6f, 0.75f);
			Colour colour2(0.7f, 0.1f, 0.25f);

			Colour newColour = colour1 - colour2;

			Assert::AreEqual(0.2f, newColour.getR(), EPSILON_TEST);
			Assert::AreEqual(0.5f, newColour.getG(), EPSILON_TEST);
			Assert::AreEqual(0.5f, newColour.getB(), EPSILON_TEST);
		}

		TEST_METHOD(TestColourMultiplicationScalar)
		{
			Colour colour(0.2f, 0.3f, 0.4f);

			Colour newColour = colour * 2;

			Assert::AreEqual(0.4f, newColour.getR(), EPSILON_TEST);
			Assert::AreEqual(0.6f, newColour.getG(), EPSILON_TEST);
			Assert::AreEqual(0.8f, newColour.getB(), EPSILON_TEST);
		}

		TEST_METHOD(TestColourMultiplicationWithAnotherColour)
		{
			Colour colour1(1.0f, 0.2f, 0.4f);
			Colour colour2(0.9f, 1.0f, 0.1f);

			Colour newColour = colour1 * colour2;

			Assert::AreEqual(0.9f, newColour.getR(), EPSILON_TEST);
			Assert::AreEqual(0.2f, newColour.getG(), EPSILON_TEST);
			Assert::AreEqual(0.04f, newColour.getB(), EPSILON_TEST);
		}
	};
}