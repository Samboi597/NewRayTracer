#include "pch.h"
#include "CppUnitTest.h"
#include "Canvas.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CanvasTest
{
	TEST_CLASS(CanvasTest)
	{
	public:

		TEST_METHOD(TestCanvasConstruction)
		{
			Canvas canvas(10, 20);

			Assert::AreEqual(10, canvas.getWidth(), EPSILON_TEST);
			Assert::AreEqual(20, canvas.getHeight(), EPSILON_TEST);

			for (int i = 0; i < canvas.getHeight(); i++)
			{
				for (int j = 0; j < canvas.getWidth(); j++)
				{
					Assert::IsTrue(canvas.getPixelColour(j, i) == Colour(0.0f, 0.0f, 0.0f));
				}
			}
		}

		TEST_METHOD(TestCanvasWritePixel)
		{
			Canvas canvas(10, 20);
			Colour red(1.0f, 0.0f, 0.0f);

			canvas.setPixelColour(2, 3, red);

			Assert::IsTrue(canvas.getPixelColour(2, 3) == red);
		}
	};
}