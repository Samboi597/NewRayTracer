#include "pch.h"
#include "CppUnitTest.h"
#include "Camera.cpp"
#include "Scene.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CameraTest
{
	TEST_CLASS(CameraTest)
	{
	public:

		TEST_METHOD(TestCameraContruction)
		{
			Camera c(160, 120, PI / 2);

			Assert::AreEqual(160, c.getWidth());
			Assert::AreEqual(120, c.getHeight());
			Assert::AreEqual(PI / 2, c.getFieldOfView(), EPSILON_TEST);
			Assert::IsTrue(identity(4) == c.getTransform());
		}

		TEST_METHOD(TestCameraPixelSizeHorizontalImage)
		{
			Camera c(200, 125, PI / 2);
			Assert::AreEqual(0.01f, c.getPixelSize(), EPSILON_TEST);
		}

		TEST_METHOD(TestCameraPixelSizeVerticalImage)
		{
			Camera c(125, 200, PI / 2);
			Assert::AreEqual(0.01f, c.getPixelSize(), EPSILON_TEST);
		}

		TEST_METHOD(TestCameraRayThroughImageCentre)
		{
			Camera c(201, 101, PI / 2);

			Ray r = c.rayForPixel(100, 50);

			Assert::IsTrue(Point(0, 0, 0) == r.getOrigin());
			Assert::AreEqual(0.0f, r.getDirection().getX(), EPSILON_TEST);
			Assert::AreEqual(0.0f, r.getDirection().getY(), EPSILON_TEST);
			Assert::AreEqual(-1.0f, r.getDirection().getZ(), EPSILON_TEST);
		}

		TEST_METHOD(TestCameraRayThroughImageCorner)
		{
			Camera c(201, 101, PI / 2);

			Ray r = c.rayForPixel(0, 0);

			Assert::IsTrue(Point(0, 0, 0) == r.getOrigin());
			Assert::AreEqual(0.66519f, r.getDirection().getX(), EPSILON_TEST);
			Assert::AreEqual(0.33259f, r.getDirection().getY(), EPSILON_TEST);
			Assert::AreEqual(-0.66851f, r.getDirection().getZ(), EPSILON_TEST);
		}

		TEST_METHOD(TestCameraRayWithTransformedCamera)
		{
			Camera c(201, 101, PI / 2);

			c.setTransform(rotationY(PI / 4) * translation(0.0f, -2.0f, 5.0f));
			Ray r = c.rayForPixel(100, 50);

			Assert::AreEqual(0.0f, r.getOrigin().getX(), EPSILON_TEST);
			Assert::AreEqual(2.0f, r.getOrigin().getY(), EPSILON_TEST);
			Assert::AreEqual(-5.0f, r.getOrigin().getZ(), EPSILON_TEST);

			Assert::AreEqual((float)sqrt(2) / 2.0f, r.getDirection().getX(), EPSILON_TEST);
			Assert::AreEqual(0.0f, r.getDirection().getY(), EPSILON_TEST);
			Assert::AreEqual((float)-sqrt(2) / 2.0f, r.getDirection().getZ(), EPSILON_TEST);
		}

		TEST_METHOD(TestCameraRenderScene)
		{
			Scene scene;
			Camera c(11, 11, PI / 2);
			Point from(0.0f, 0.0f, -5.0f);
			Point to(0.0f, 0.0f, 0.0f);
			Vector up(0.0f, 1.0f, 0.0f);

			c.setTransform(viewTransform(from, to, up));

			Canvas image = c.render(scene);

			Colour imageAt = image.getPixelColour(5, 5);
			Assert::AreEqual(0.38066f, imageAt.getR(), EPSILON_TEST);
			Assert::AreEqual(0.47583f, imageAt.getG(), EPSILON_TEST);
			Assert::AreEqual(0.2855f, imageAt.getB(), EPSILON_TEST);
		}
	};
}