#include "Squares.h"

Square::Square( int MinRed, int MinGreen, int MinBlue,
				int MaxRed, int MaxGreen, int MaxBlue,
				int Left, int Top, int Right, int Bottom )
	:
	maxRed( MaxRed ), minRed( MinRed ), red( MinRed ),
	maxGreen( MaxGreen ), minGreen( MinGreen ), green( MinGreen ),
	maxBlue( MaxBlue ), minBlue( MinBlue ), blue( MinBlue ),
	left( Left ), top( Top ), right( Right ), bottom( Bottom )
{
}

void Square::ResetColor()
{
	red = minRed;
	green = minGreen;
	blue = minBlue;
}

bool Square::MouseOver( int MX, int MY ) const
{
	return
		MX > left && MX <= right &&
		MY > top && MY <= bottom;
}

void Square::Draw( Graphics & Gfx ) const
{
	for( int y = top; y < bottom; ++y )
	{
		for( int x = left; x < right; ++x )
		{
			Gfx.PutPixel( x, y, red, green, blue );
		}
	}
}
