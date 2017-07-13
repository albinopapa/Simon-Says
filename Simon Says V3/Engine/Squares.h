#pragma once

#include "Graphics.h"

class Square
{
public:
	Square( int MinRed, int MinGreen, int MinBlue, 
			int MaxRed, int MaxGreen, int MaxBlue, 
			int Left, int Top, int Right, int Bottom );

	bool MouseOver( int MX, int MY )const;
	void Draw( Graphics &Gfx )const;
public:
	int red, maxRed, minRed;
	int green, maxGreen, minGreen;
	int blue, maxBlue, minBlue;
	int left, top, right, bottom;
};

