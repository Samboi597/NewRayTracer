#include "pch.h"
#include "CppUnitTest.h"
#include "Matrix.cpp"
#include "Point.h"

#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MatrixTest
{
	TEST_CLASS(MatrixTest)
	{
	public:

		TEST_METHOD(TestMatrix4x4Construction)
		{
			vector<vector<float>> matrix = {
				{ 1.0f, 2.0f, 3.0f, 4.0f },
				{ 5.5f, 6.5f, 7.5f, 8.5f },
				{ 9.0f, 10.0f, 11.0f, 12.0f },
				{ 13.5f, 14.5f, 15.5f, 16.5f }
			};

			Matrix m(4, 4, matrix);

			Assert::AreEqual(4, m.getRows());
			Assert::AreEqual(4, m.getColumns());

			Assert::AreEqual(1.0f, m.get(0, 0), EPSILON_TEST);
			Assert::AreEqual(4.0f, m.get(0, 3), EPSILON_TEST);
			Assert::AreEqual(5.5f, m.get(1, 0), EPSILON_TEST);
			Assert::AreEqual(7.5f, m.get(1, 2), EPSILON_TEST);
			Assert::AreEqual(11.0f, m.get(2, 2), EPSILON_TEST);
			Assert::AreEqual(13.5f, m.get(3, 0), EPSILON_TEST);
			Assert::AreEqual(15.5f, m.get(3, 2), EPSILON_TEST);
		}

		TEST_METHOD(TestMatrix2x2Construction)
		{
			vector<vector<float>> matrix = {
				{ -3.0f, 5.0f },
				{ 1.0f, -2.0f }
			};

			Matrix m(2, 2, matrix);

			Assert::AreEqual(-3.0f, m.get(0, 0), EPSILON_TEST);
			Assert::AreEqual(5.0f, m.get(0, 1), EPSILON_TEST);
			Assert::AreEqual(1.0f, m.get(1, 0), EPSILON_TEST);
			Assert::AreEqual(-2.0f, m.get(1, 1), EPSILON_TEST);
		}

		TEST_METHOD(TestMatrix3x3Construction)
		{
			vector<vector<float>> matrix = {
				{ -3.0f, 5.0f, 0.0f },
				{ 1.0f, -2.0f, -7.0f },
				{ 0.0f, 1.0f, 1.0f }
			};

			Matrix m(3, 3, matrix);

			Assert::AreEqual(-3.0f, m.get(0, 0), EPSILON_TEST);
			Assert::AreEqual(-2.0f, m.get(1, 1), EPSILON_TEST);
			Assert::AreEqual(1.0f, m.get(2, 2), EPSILON_TEST);
		}

		TEST_METHOD(TestMatrixEqualityTrue)
		{
			vector<vector<float>> a = {
				{ 1.0f, 2.0f, 3.0f, 4.0f },
				{ 5.0f, 6.0f, 7.0f, 8.0f },
				{ 9.0f, 8.0f, 7.0f, 6.0f },
				{ 5.0f, 4.0f, 3.0f, 2.0f }
			};

			vector<vector<float>> b = {
				{ 1.0f, 2.0f, 3.0f, 4.0f },
				{ 5.0f, 6.0f, 7.0f, 8.0f },
				{ 9.0f, 8.0f, 7.0f, 6.0f },
				{ 5.0f, 4.0f, 3.0f, 2.0f }
			};

			Matrix l(4, 4, a);
			Matrix r(4, 4, b);

			Assert::IsTrue(l == r);
		}

		TEST_METHOD(TestMatrixEqualityFalse)
		{
			vector<vector<float>> a = {
				{ 1.0f, 2.0f, 3.0f, 4.0f },
				{ 5.0f, 6.0f, 7.0f, 8.0f },
				{ 9.0f, 8.0f, 7.0f, 6.0f },
				{ 5.0f, 4.0f, 3.0f, 2.0f }
			};

			vector<vector<float>> b = {
				{ 2.0f, 3.0f, 4.0f, 5.0f },
				{ 6.0f, 7.0f, 8.0f, 9.0f },
				{ 8.0f, 7.0f, 6.0f, 5.0f },
				{ 4.0f, 3.0f, 2.0f, 1.0f }
			};

			Matrix l(4, 4, a);
			Matrix r(4, 4, b);

			Assert::IsFalse(l == r);
		}

		TEST_METHOD(TestMatrixMultiplication)
		{
			vector<vector<float>> a = {
				{ 1.0f, 2.0f, 3.0f, 4.0f },
				{ 5.0f, 6.0f, 7.0f, 8.0f },
				{ 9.0f, 8.0f, 7.0f, 6.0f },
				{ 5.0f, 4.0f, 3.0f, 2.0f }
			};

			vector<vector<float>> b = {
				{ -2.0f, 1.0f, 2.0f, 3.0f },
				{ 3.0f, 2.0f, 1.0f, -1.0f },
				{ 4.0f, 3.0f, 6.0f, 5.0f },
				{ 1.0f, 2.0f, 7.0f, 8.0f }
			};

			vector<vector<float>> c = {
				{ 20.0f, 22.0f, 50.0f, 48.0f },
				{ 44.0f, 54.0f, 114.0f, 108.0f },
				{ 40.0f, 58.0f, 110.0f, 102.0f },
				{ 16.0f, 26.0f, 46.0f, 42.0f }
			};

			Matrix l(4, 4, a);
			Matrix r(4, 4, b);
			Matrix expected(4, 4, c);

			Assert::IsTrue(expected == l * r);
		}

		TEST_METHOD(TestMatrixMultiplicationTuple)
		{
			vector<vector<float>> a = {
				{ 1.0f, 2.0f, 3.0f, 4.0f },
				{ 2.0f, 4.0f, 4.0f, 2.0f },
				{ 8.0f, 6.0f, 4.0f, 1.0f },
				{ 0.0f, 0.0f, 0.0f, 1.0f }
			};

			Tuple t(1.0f, 2.0f, 3.0f, 1.0f);
			Tuple expected(18.0f, 24.0f, 33.0f, 1.0f);

			Matrix m(4, 4, a);

			Assert::IsTrue(expected == m * t);
		}

		TEST_METHOD(TestMatrixIdentity)
		{
			vector<vector<float>> a = {
				{ 0.0f, 1.0f, 2.0f, 4.0f },
				{ 1.0f, 2.0f, 4.0f, 8.0f },
				{ 2.0f, 4.0f, 8.0f, 16.0f },
				{ 4.0f, 8.0f, 16.0f, 32.0f }
			};

			Matrix m(4, 4, a);
			Matrix i = identity(4);

			Assert::IsTrue(m == m * i);
		}

		TEST_METHOD(TestMatrixIdentityTuple)
		{
			Matrix m(4, 4);
			Tuple t(1.0f, 2.0f, 3.0f, 4.0f);

			Matrix i = identity(4);

			Assert::IsTrue(t == i * t);
		}

		TEST_METHOD(TestMatrixTranspose)
		{
			vector<vector<float>> a = {
				{ 0.0f, 9.0f, 3.0f, 0.0f },
				{ 9.0f, 8.0f, 0.0f, 8.0f },
				{ 1.0f, 8.0f, 5.0f, 3.0f },
				{ 0.0f, 0.0f, 5.0f, 8.0f }
			};

			vector<vector<float>> b = {
				{ 0.0f, 9.0f, 1.0f, 0.0f },
				{ 9.0f, 8.0f, 8.0f, 0.0f },
				{ 3.0f, 0.0f, 5.0f, 5.0f },
				{ 0.0f, 8.0f, 3.0f, 8.0f }
			};

			Matrix l(4, 4, a);
			Matrix r(4, 4, b);

			Assert::IsTrue(r == l.transpose());
		}

		TEST_METHOD(TestMatrixIdentityTranspose)
		{
			Matrix i = identity(4);

			Assert::IsTrue(i == i.transpose());
		}

		TEST_METHOD(TestMatrixDeterminant2x2)
		{
			vector<vector<float>> a = {
				{ 1.0f, 5.0f },
				{ -3.0f, 2.0f }
			};

			Matrix m(2, 2, a);

			Assert::AreEqual(17.0f, m.determinant(), EPSILON_TEST);
		}

		TEST_METHOD(TestMatrixDeterminant3x3)
		{
			vector<vector<float>> a = {
				{ 1.0f, 2.0f, 6.0f },
				{ -5.0f, 8.0f, -4.0f },
				{ 2.0f, 6.0f, 4.0f }
			};

			Matrix m(3, 3, a);

			Assert::AreEqual(-196.0f, m.determinant(), EPSILON_TEST);
		}

		TEST_METHOD(TestMatrixDeterminant4x4)
		{
			vector<vector<float>> a = {
				{ -2.0f, -8.0f, 3.0f, 5.0f },
				{ -3.0f, 1.0f, 7.0f, 3.0f },
				{ 1.0f, 2.0f, -9.0f, 6.0f },
				{ -6.0f, 7.0f, 7.0f, -9.0f }
			};

			Matrix m(4, 4, a);

			Assert::AreEqual(-4071.0f, m.determinant(), EPSILON_TEST);
		}

		TEST_METHOD(TestMatrixSubmatrix2x2)
		{
			vector<vector<float>> a = {
				{ 1.0f, 5.0f, 0.0f },
				{ -3.0f, 2.0f, 7.0f },
				{ 0.0f, 6.0f, -3.0f }
			};

			vector<vector<float>> b = {
				{ -3.0f, 2.0f },
				{ 0.0f, 6.0f }
			};

			Matrix m(3, 3, a);
			Matrix expected(2, 2, b);

			Assert::IsTrue(expected == m.submatrix(0, 2));
		}

		TEST_METHOD(TestMatrixSubmatrix3x3)
		{
			vector<vector<float>> a = {
				{ -6.0f, 1.0f, 1.0f, 6.0f },
				{ -8.0f, 5.0f, 8.0f, 6.0f },
				{ -1.0f, 0.0f, 8.0f, 2.0f },
				{ -7.0f, 1.0f, -1.0f, 1.0f }
			};

			vector<vector<float>> b = {
				{ -6.0f, 1.0f, 6.0f },
				{ -8.0f, 8.0f, 6.0f },
				{ -7.0f, -1.0f, 1.0f }
			};

			Matrix m(4, 4, a);
			Matrix expected(3, 3, b);

			Assert::IsTrue(expected == m.submatrix(2, 1));
		}

		TEST_METHOD(TestMatrixMinor)
		{
			vector<vector<float>> a = {
				{ 3.0f, 5.0f, 0.0f },
				{ 2.0f, -1.0f, -7.0f },
				{ 6.0f, -1.0f, 5.0f }
			};

			Matrix m(3, 3, a);

			Assert::AreEqual(25.0f, m.minor(1, 0), EPSILON_TEST);
		}

		TEST_METHOD(TestMatrixCofactor)
		{
			vector<vector<float>> a = {
				{ 3.0f, 5.0f, 0.0f },
				{ 2.0f, -1.0f, -7.0f },
				{ 6.0f, -1.0f, 5.0f }
			};

			Matrix m(3, 3, a);

			Assert::AreEqual(-12.0f, m.minor(0, 0), EPSILON_TEST);
			Assert::AreEqual(-12.0f, m.cofactor(0, 0), EPSILON_TEST);
			Assert::AreEqual(25.0f, m.minor(1, 0), EPSILON_TEST);
			Assert::AreEqual(-25.0f, m.cofactor(1, 0), EPSILON_TEST);
		}

		TEST_METHOD(TestMatrixInvertible)
		{
			vector<vector<float>> a = {
				{ 6.0f, 4.0f, 4.0f, 4.0f },
				{ 5.0f, 5.0f, 7.0f, 6.0f },
				{ 4.0f, -9.0f, 3.0f, -7.0f },
				{ 9.0f, 1.0f, 7.0f, -6.0f }
			};

			Matrix m(4, 4, a);

			Assert::IsTrue(m.isInvertible());
		}

		TEST_METHOD(TestMatrixNotInvertible)
		{
			vector<vector<float>> a = {
				{ -4.0f, 2.0f, -2.0f, -3.0f },
				{ 9.0f, 6.0f, 2.0f, 6.0f },
				{ 0.0f, -5.0f, 1.0f, -5.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f }
			};

			Matrix m(4, 4, a);

			Assert::IsFalse(m.isInvertible());
		}

		TEST_METHOD(TestMatrixInverseA)
		{
			vector<vector<float>> a = {
				{ -5.0f, 2.0f, 6.0f, -8.0f },
				{ 1.0f, -5.0f, 1.0f, 8.0f },
				{ 7.0f, 7.0f, -6.0f, -7.0f },
				{ 1.0f, -3.0f, 7.0f, 4.0f }
			};

			vector<vector<float>> b = {
				{ 0.21805f, 0.45113f, 0.24060f, -0.04511f },
				{ -0.80827f, -1.45677f, -0.44361f, 0.52068f },
				{ -0.07895f, -0.22368f, -0.05263f, 0.19737f },
				{ -0.52256f, -0.81391f, -0.30075f, 0.30639f }
			};

			Matrix m(4, 4, a);
			Matrix expected(4, 4, b);

			Assert::AreEqual(532.0f, m.determinant(), EPSILON_TEST);
			Assert::AreEqual(-160.0f, m.cofactor(2, 3), EPSILON_TEST);
			Assert::AreEqual(-160.0f / 532.0f, expected.get(3, 2), EPSILON_TEST);
			Assert::AreEqual(105.0f, m.cofactor(3, 2), EPSILON_TEST);
			Assert::AreEqual(105.0f / 532.0f, expected.get(2, 3), EPSILON_TEST);
			Assert::IsTrue(expected == m.inverse());
		}

		TEST_METHOD(TestMatrixInverseB)
		{
			vector<vector<float>> a = {
				{ 8.0f, -5.0f, 9.0f, 2.0f },
				{ 7.0f, 5.0f, 6.0f, 1.0f },
				{ -6.0f, 0.0f, 9.0f, 6.0f },
				{ -3.0f, 0.0f, -9.0f, -4.0f }
			};

			vector<vector<float>> b = {
				{ -0.15385f, -0.15385f, -0.28205f, -0.53846f },
				{ -0.07692f, 0.12308f, 0.02564f, 0.03077f },
				{ 0.35897f, 0.35897f, 0.43590f, 0.92308f },
				{ -0.69231f, -0.69231f, -0.76923f, -1.92308f }
			};

			Matrix m(4, 4, a);
			Matrix expected(4, 4, b);

			Assert::IsTrue(expected == m.inverse());
		}

		TEST_METHOD(TestMatrixInverseC)
		{
			vector<vector<float>> a = {
				{ 9.0f, 3.0f, 0.0f, 9.0f },
				{ -5.0f, -2.0f, -6.0f, -3.0f },
				{ -4.0f, 9.0f, 6.0f, 4.0f },
				{ -7.0f, 6.0f, 6.0f, 2.0f }
			};

			vector<vector<float>> b = {
				{ -0.04074f, -0.07778f, 0.14444f, -0.22222f },
				{ -0.07778f, 0.03333f, 0.36667f, -0.33333f },
				{ -0.02901f, -0.14630f, -0.10926f, 0.12963f },
				{ 0.17778f, 0.06667f, -0.26667f, 0.33333f }
			};

			Matrix m(4, 4, a);
			Matrix expected(4, 4, b);

			Assert::IsTrue(expected == m.inverse());
		}

		TEST_METHOD(TestMatrixMultiplyProductByInverse)
		{
			vector<vector<float>> a = {
				{ 3.0f, -9.0f, 7.0f, 3.0f },
				{ 3.0f, -8.0f, 2.0f, -9.0f },
				{ -4.0f, 4.0f, 4.0f, 1.0f },
				{ -6.0f, 5.0f, -1.0f, 1.0f }
			};

			vector<vector<float>> b = {
				{ 8.0f, 2.0f, 2.0f, 2.0f },
				{ 3.0f, -1.0f, 7.0f, 0.0f },
				{ 7.0f, 0.0f, 5.0f, 4.0f },
				{ 6.0f, -2.0f, 0.0f, 5.0f }
			};

			Matrix l(4, 4, a);
			Matrix r(4, 4, b);
			Matrix i = l * r * r.inverse();

			Assert::IsTrue(l == i);
		}

		TEST_METHOD(TestTranslationMatrixPoint)
		{
			Matrix transform = translation(5.0f, -3.0f, 2.0f);
			Point point(-3.0f, 4.0f, 5.0f);

			Assert::IsTrue(Tuple(2.0f, 1.0f, 7.0f, 1.0f) == transform * point);
		}

		TEST_METHOD(TestTranslationMatrixInverse)
		{
			Matrix transform = translation(5.0f, -3.0f, 2.0f);
			Matrix inverse = transform.inverse();
			Point point(-3.0f, 4.0f, 5.0f);

			Assert::IsTrue(Point(-8.0f, 7.0f, 3.0f) == inverse * point);
		}

		TEST_METHOD(TestTranslationMatrixVectors)
		{
			Matrix transform = translation(5.0f, -3.0f, 2.0f);
			Vector vector(-3.0f, 4.0f, 5.0f);

			Assert::IsTrue(vector == transform * vector);
		}

		TEST_METHOD(TestScalingMatrixPoint)
		{
			Matrix transform = scaling(2.0f, 3.0f, 4.0f);
			Point point(-4.0f, 6.0f, 8.0f);

			Assert::IsTrue(Point(-8.0f, 18.0f, 32.0f) == transform * point);
		}

		TEST_METHOD(TestScalingMatrixInverse)
		{
			Matrix transform = scaling(2.0f, 3.0f, 4.0f);
			Matrix inverse = transform.inverse();
			Point point(-4.0f, 6.0f, 8.0f);

			Assert::IsTrue(Point(-2.0f, 2.0f, 2.0f) == inverse * point);
		}

		TEST_METHOD(TestScalingMatrixVector)
		{
			Matrix transform = scaling(2.0f, 3.0f, 4.0f);
			Vector vector(-4.0f, 6.0f, 8.0f);

			Assert::IsTrue(Vector(-8.0f, 18.0f, 32.0f) == transform * vector);
		}

		TEST_METHOD(TestScalingMatrixReflection)
		{
			Matrix transform = scaling(-1.0f, 1.0f, 1.0f);
			Point point(2.0f, 3.0f, 4.0f);

			Assert::IsTrue(Point(-2.0f, 3.0f, 4.0f) == transform * point);
		}

		TEST_METHOD(TestMatrixRotationX)
		{
			Point point(0.0f, 1.0f, 0.0f);
			Matrix half_quarter = rotationX(PI / 4.0f);
			Matrix full_quarter = rotationX(PI / 2.0f);

			Assert::AreEqual(0.0f, (half_quarter * point).getX(), EPSILON_TEST);
			Assert::AreEqual((sqrt(2.0f) / 2.0f), (half_quarter * point).getY(), EPSILON_TEST);
			Assert::AreEqual((sqrt(2.0f) / 2.0f), (half_quarter * point).getZ(), EPSILON_TEST);
			Assert::AreEqual(1.0f, (half_quarter * point).getW(), EPSILON_TEST);

			Assert::AreEqual(0.0f, (full_quarter * point).getX(), EPSILON_TEST);
			Assert::AreEqual(0.0f, (full_quarter * point).getY(), EPSILON_TEST);
			Assert::AreEqual(1.0f, (full_quarter * point).getZ(), EPSILON_TEST);
			Assert::AreEqual(1.0f, (full_quarter * point).getW(), EPSILON_TEST);
		}

		TEST_METHOD(TestMatrixRotationXInverse)
		{
			Point point(0.0f, 1.0f, 0.0f);
			Matrix half_quarter = rotationX(PI / 4.0f);

			Matrix inverse = half_quarter.inverse();

			Assert::AreEqual(0.0f, (inverse * point).getX(), EPSILON_TEST);
			Assert::AreEqual((sqrt(2.0f) / 2.0f), (inverse * point).getY(), EPSILON_TEST);
			Assert::AreEqual(-(sqrt(2.0f) / 2.0f), (inverse * point).getZ(), EPSILON_TEST);
			Assert::AreEqual(1.0f, (inverse * point).getW(), EPSILON_TEST);
		}

		TEST_METHOD(TestMatrixRotationY)
		{
			Point point(0.0f, 0.0f, 1.0f);
			Matrix half_quarter = rotationY(PI / 4.0f);
			Matrix full_quarter = rotationY(PI / 2.0f);

			Assert::AreEqual((sqrt(2.0f) / 2.0f), (half_quarter * point).getX(), EPSILON_TEST);
			Assert::AreEqual(0.0f, (half_quarter * point).getY(), EPSILON_TEST);
			Assert::AreEqual((sqrt(2.0f) / 2.0f), (half_quarter * point).getZ(), EPSILON_TEST);
			Assert::AreEqual(1.0f, (half_quarter * point).getW(), EPSILON_TEST);

			Assert::AreEqual(1.0f, (full_quarter * point).getX(), EPSILON_TEST);
			Assert::AreEqual(0.0f, (full_quarter * point).getY(), EPSILON_TEST);
			Assert::AreEqual(0.0f, (full_quarter * point).getZ(), EPSILON_TEST);
			Assert::AreEqual(1.0f, (full_quarter * point).getW(), EPSILON_TEST);
		}

		TEST_METHOD(TestMatrixRotationZ)
		{
			Point point(0.0f, 1.0f, 0.0f);
			Matrix half_quarter = rotationZ(PI / 4.0f);
			Matrix full_quarter = rotationZ(PI / 2.0f);

			Assert::AreEqual(-(sqrt(2.0f) / 2.0f), (half_quarter * point).getX(), EPSILON_TEST);
			Assert::AreEqual((sqrt(2.0f) / 2.0f), (half_quarter * point).getY(), EPSILON_TEST);
			Assert::AreEqual(0.0f, (half_quarter * point).getZ(), EPSILON_TEST);
			Assert::AreEqual(1.0f, (half_quarter * point).getW(), EPSILON_TEST);

			Assert::AreEqual(-1.0f, (full_quarter * point).getX(), EPSILON_TEST);
			Assert::AreEqual(0.0f, (full_quarter * point).getY(), EPSILON_TEST);
			Assert::AreEqual(0.0f, (full_quarter * point).getZ(), EPSILON_TEST);
			Assert::AreEqual(1.0f, (full_quarter * point).getW(), EPSILON_TEST);
		}

		TEST_METHOD(TestMatrixShearingXInProportionToY)
		{
			Matrix transform = shearing(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			Point point(2.0f, 3.0f, 4.0f);

			Assert::IsTrue(Point(5.0f, 3.0f, 4.0f) == transform * point);
		}

		TEST_METHOD(TestMatrixShearingXInProportionToZ)
		{
			Matrix transform = shearing(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
			Point point(2.0f, 3.0f, 4.0f);

			Assert::IsTrue(Point(6.0f, 3.0f, 4.0f) == transform * point);
		}

		TEST_METHOD(TestMatrixShearingYInProportionToX)
		{
			Matrix transform = shearing(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
			Point point(2.0f, 3.0f, 4.0f);

			Assert::IsTrue(Point(2.0f, 5.0f, 4.0f) == transform * point);
		}

		TEST_METHOD(TestMatrixShearingYInProportionToZ)
		{
			Matrix transform = shearing(0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
			Point point(2.0f, 3.0f, 4.0f);

			Assert::IsTrue(Point(2.0f, 7.0f, 4.0f) == transform * point);
		}

		TEST_METHOD(TestMatrixShearingZInProportionToX)
		{
			Matrix transform = shearing(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
			Point point(2.0f, 3.0f, 4.0f);

			Assert::IsTrue(Point(2.0f, 3.0f, 6.0f) == transform * point);
		}

		TEST_METHOD(TestMatrixShearingZInProportionToY)
		{
			Matrix transform = shearing(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
			Point point(2.0f, 3.0f, 4.0f);

			Assert::IsTrue(Point(2.0f, 3.0f, 7.0f) == transform * point);
		}
	};
}