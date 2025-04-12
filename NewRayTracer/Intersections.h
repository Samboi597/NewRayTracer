#pragma once

#include <algorithm>
#include <vector>
#include "Intersection.h"

using namespace std;

class Intersections
{
private:
	vector<Intersection> data;

public:
	Intersections() : data() {}
	Intersections(vector<Intersection> const& newData) : data(newData) {}

	Intersection const getIntersection(int i) { return data[i]; }
	int const getCount() { return (int)(data.size()); }
	Intersection const getHit();

	void push_back(Intersection const& x) { data.push_back(x); }
	void sortData() { sort(data.begin(), data.end(), [](Intersection const& a, Intersection const& b) { return a.getT() < b.getT(); }); }
};
