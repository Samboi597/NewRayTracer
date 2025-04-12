#pragma once
#include "Point.h"
#include <vector>

using namespace std;

extern const float EPSILON;

class Matrix
{
private:
	int rows;
	int columns;
	vector<vector<float>> data;

public:
	Matrix(int const &newRows, int const &newColumns) : rows(newRows), columns(newColumns), data(newRows, vector<float>(newColumns, 0.0f)) {}
	Matrix(int const &newRows, int const &newColumns, vector<vector<float>> &newData);

	int getRows() const { return rows; }
	int getColumns() const { return columns; }
	float get(int const &row, int const &column) const { return data[row][column]; }
	void set(int const &row, int const &column, float const& value) { data[row][column] = value; }

	bool operator==(Matrix const &other) const;
	Matrix operator*(Matrix const &other) const;
	Tuple operator*(Tuple const &tuple) const;

	Matrix transpose() const;
	float determinant() const;
	Matrix submatrix(int const &row, int const &column) const;
	float minor(int const &row, int const &column) const { return submatrix(row, column).determinant(); }
	float cofactor(int const &row, int const &column) const { return minor(row, column) * ((row + column) % 2 == 0 ? 1 : -1); }
	bool isInvertible() const { return determinant() != 0.0f; }
	Matrix inverse() const;
};

static Matrix identity(int const& size)
{
	Matrix result(size, size);

	for (int i = 0; i < size; i++) { result.set(i, i, 1.0f); }

	return result;
}

static Matrix translation(float const& x, float const& y, float const& z)
{
	Matrix result = identity(4);

	result.set(0, 3, x);
	result.set(1, 3, y);
	result.set(2, 3, z);

	return result;
}

static Matrix scaling(float const& x, float const& y, float const& z)
{
	Matrix result = identity(4);

	result.set(0, 0, x);
	result.set(1, 1, y);
	result.set(2, 2, z);

	return result;
}

static Matrix rotationX(float const& radians)
{
	Matrix result = identity(4);

	result.set(1, 1, cos(radians));
	result.set(1, 2, -sin(radians));
	result.set(2, 1, sin(radians));
	result.set(2, 2, cos(radians));

	return result;
}

static Matrix rotationY(float const& radians)
{
	Matrix result = identity(4);

	result.set(0, 0, cos(radians));
	result.set(0, 2, sin(radians));
	result.set(2, 0, -sin(radians));
	result.set(2, 2, cos(radians));

	return result;
}

static Matrix rotationZ(float const& radians)
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

static Matrix viewTransform(Point const& from, Point const& to, Vector const& up)
{
	Vector forward = (to - from).normalise();
	Vector upon = up.normalise();
	Vector left = forward.cross(upon);
	Vector trueUp = left.cross(forward);

	Matrix orientation(4, 4);
	orientation.set(0, 0, left.getX());
	orientation.set(0, 1, left.getY());
	orientation.set(0, 2, left.getZ());
	orientation.set(1, 0, trueUp.getX());
	orientation.set(1, 1, trueUp.getY());
	orientation.set(1, 2, trueUp.getZ());
	orientation.set(2, 0, -forward.getX());
	orientation.set(2, 1, -forward.getY());
	orientation.set(2, 2, -forward.getZ());
	orientation.set(3, 3, 1.0f);

	return orientation * translation(-from.getX(), -from.getY(), -from.getZ());
}
