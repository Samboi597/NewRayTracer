#pragma once
#include "Tuple.h"
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
