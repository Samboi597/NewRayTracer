#include "PPMWriter.h"

void PPMWriter::writeHeader(ostream& stream, Canvas const& canvas) const
{
	stream << "P3\n";
	stream << canvas.getWidth() << " " << canvas.getHeight() << "\n";
	stream << MAX_COLOR_VALUE << "\n";
}

void PPMWriter::writeColour(ostream& stream, float const& colourFloat, int& lineLength) const
{
	int colourInt, colourLength = 0;

	if (colourFloat >= 1.0f) { colourInt = 255; }
	else if (colourFloat < 0.0f) { colourInt = 0; }
	else { colourInt = ceil(colourFloat * 255); }

	if (colourInt >= 100) { colourLength = 3; }
	else if (colourInt >= 10) { colourLength = 2; }
	else { colourLength = 1; }

	bool spaceBefore = lineLength != 0;
	if ((lineLength + colourLength + spaceBefore) >= MAX_LINE_LEN) {
		stream << "\n";
		lineLength = 0;
	}
	else if (spaceBefore) {
		stream << " ";
		lineLength += 1;
	}

	lineLength += colourLength;
	stream << colourInt;
}

void PPMWriter::writeStream(ostream& stream, Canvas const& canvas) const
{
	writeHeader(stream, canvas);

	for (int y = 0; y < canvas.getHeight(); y++)
	{
		int lineLength = 0;

		for (int x = 0; x < canvas.getWidth(); x++)
		{
			Colour colour = canvas.getPixelColour(x, y);

			writeColour(stream, colour.getR(), lineLength);
			writeColour(stream, colour.getG(), lineLength);
			writeColour(stream, colour.getB(), lineLength);

			if (x == canvas.getWidth() - 1) { stream << "\n"; }
		}
	}
}

void PPMWriter::writeFile(string filename, Canvas const& canvas) const
{
	ofstream file;
	file.open(filename);
	writeStream(file, canvas);
	file.close();
}
