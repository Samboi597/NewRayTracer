#pragma once

#include <vector>
#include "Intersection.h"

using namespace std;

class Intersections
{
private:
	vector<Intersection> data;

public:
	Intersections(vector<Intersection> const &newData) : data(newData) {}

	Intersection const getIntersection(int i) { return data[i]; }
	int const getCount() { return data.size(); }
	Intersection const getHit();
};
