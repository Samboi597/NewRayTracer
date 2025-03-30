#pragma once
#include "Canvas.h"

#include <fstream>
#include <string>

using namespace std;

class PPMWriter
{
private:
	const int MAX_COLOR_VALUE = 255;
	const int MAX_LINE_LEN = 70;

	void writeHeader(ostream &stream, Canvas const &canvas) const;

public:
	PPMWriter() {}

	void writeFile(string filename, Canvas const &canvas) const;
	void writeStream(ostream &stream, Canvas const &canvas) const;
	void writeColour(ostream &stream, float const &colourFloat, int &lineLength) const;
};
