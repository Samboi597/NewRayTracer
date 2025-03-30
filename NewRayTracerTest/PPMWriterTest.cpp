#include "pch.h"
#include "CppUnitTest.h"
#include "PPMWriter.cpp"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PPMWriterTest
{
	TEST_CLASS(PPMWriterTest)
	{
	public:

		TEST_METHOD(TestWriteStream)
		{
			PPMWriter writer;
			Canvas canvas(5, 3);
			ostringstream stream;

			canvas.setPixelColour(0, 0, Colour(1.5f, 0.0f, 0.0f));
			canvas.setPixelColour(2, 1, Colour(0.0f, 0.5f, 0.0f));
			canvas.setPixelColour(4, 2, Colour(-0.5f, 0.0f, 1.0f));

			writer.writeStream(stream, canvas);

			Assert::AreEqual(string("P3\n5 3\n255\n255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"), stream.str());
		}

		TEST_METHOD(TestWriteStreamWithColourConstructor)
		{
			PPMWriter writer;
			Canvas canvas(10, 2, Colour(1.0f, 0.8f, 0.6f));
			ostringstream stream;

			writer.writeStream(stream, canvas);

			Assert::AreEqual(string("P3\n10 2\n255\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n153 255 204 153 255 204 153 255 204 153 255 204 153\n"), stream.str());
		}
	};
}