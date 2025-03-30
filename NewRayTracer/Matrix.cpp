#include "Matrix.h"

const float EPSILON = 0.00001f;

static Matrix identity(int const &size)
{
	Matrix result(size, size);

	for (int i = 0; i < size; i++) { result.set(i, i, 1.0f); }

	return result;
}

static Matrix translation(float const &x, float const &y, float const &z)
{
	Matrix result = identity(4);

	result.set(0, 3, x);
	result.set(1, 3, y);
	result.set(2, 3, z);

	return result;
}

static Matrix scaling(float const &x, float const &y, float const &z)
{
	Matrix result = identity(4);

	result.set(0, 0, x);
	result.set(1, 1, y);
	result.set(2, 2, z);

	return result;
}

static Matrix rotationX(float const &radians)
{
	Matrix result = identity(4);

	result.set(1, 1, cos(radians));
	result.set(1, 2, -sin(radians));
	result.set(2, 1, sin(radians));
	result.set(2, 2, cos(radians));

	return result;
}

static Matrix rotationY(float const &radians)
{
	Matrix result = identity(4);

	result.set(0, 0, cos(radians));
	result.set(0, 2, sin(radians));
	result.set(2, 0, -sin(radians));
	result.set(2, 2, cos(radians));

	return result;
}

static Matrix rotationZ(float const &radians)
{
	Matrix result = identity(4);

	result.set(0, 0, cos(radians));
	result.set(0, 1, -sin(radians));
	result.set(1, 0, sin(radians));
	result.set(1, 1, cos(radians));

	return result;
}

static Matrix shearing(float const& xy, float const& xz, float const& yx, float const& yz, float const& zx, float const& zy)
{
	Matrix result = identity(4);

	result.set(0, 1, xy);
	result.set(0, 2, xz);
	result.set(1, 0, yx);
	result.set(1, 2, yz);
	result.set(2, 0, zx);
	result.set(2, 1, zy);

	return result;
}

Matrix::Matrix(int const &newRows, int const &newColumns, vector<vector<float>> &newData)
{
	vector<float> newRow;

	rows = newRows;
	columns = newColumns;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++) { newRow.push_back(newData[i][j]); }

		data.push_back(newRow);
		newRow.clear();
	}
}

bool Matrix::operator==(Matrix const &other) const
{
	if (columns != other.getColumns() || rows != other.getRows()) { return false; }

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < columns; col++) {
			float l = data[row][col];
			float r = other.get(row, col);

			if (fabs(l - r) > EPSILON) { return false; }
		}
	}

	return true;
}

Matrix Matrix::operator*(Matrix const &other) const
{
	Matrix result(rows, other.getColumns());

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < other.getColumns(); col++) {
			float sum = 0.0f;

			for (int i = 0; i < columns; i++) { sum += data[row][i] * other.get(i, col); }

			result.set(row, col, sum);
		}
	}

	return result;
}

Tuple Matrix::operator*(Tuple const &tuple) const
{
	Tuple result;

	result.setX(data[0][0] * tuple.getX() + data[0][1] * tuple.getY() + data[0][2] * tuple.getZ() + data[0][3] * tuple.getW());
	result.setY(data[1][0] * tuple.getX() + data[1][1] * tuple.getY() + data[1][2] * tuple.getZ() + data[1][3] * tuple.getW());
	result.setZ(data[2][0] * tuple.getX() + data[2][1] * tuple.getY() + data[2][2] * tuple.getZ() + data[2][3] * tuple.getW());
	result.setW(data[3][0] * tuple.getX() + data[3][1] * tuple.getY() + data[3][2] * tuple.getZ() + data[3][3] * tuple.getW());

	return result;
}

Matrix Matrix::transpose() const
{
	Matrix result(columns, rows);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			result.set(j, i, data[i][j]);
		}
	}

	return result;
}

float Matrix::determinant() const
{
	float result;
	int size = data.size();

	switch (size)
	{
	case 1:
		result = data[0][0];
		break;
	case 2:
		result = data[0][0] * data[1][1] - data[0][1] * data[1][0];
		break;
	default:
		result = 0.0f;

		for (int i = 0; i < columns; i++) {
			result += data[0][i] * cofactor(0, i);
		}

		break;
	}

	return result;
}

Matrix Matrix::submatrix(int const &row, int const &column) const
{
	Matrix sub(rows - 1, columns - 1);

	int subRow = 0, subColumn;

	for (int i = 0; i < rows; i++) {
		if (i == row) { continue; }

		subColumn = 0;

		for (int j = 0; j < columns; j++) {
			if (j == column) { continue; }

			sub.set(subRow, subColumn, data[i][j]);

			subColumn++;
		}

		subRow++;
	}

	return sub;
}

Matrix Matrix::inverse() const
{
	float invDet = 1.0f / determinant();

	Matrix result(rows, columns);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			float c = cofactor(j, i);
			result.set(i, j, c * invDet);
		}
	}

	return result;
}
