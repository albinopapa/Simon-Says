#pragma once

class Square
{
public:
	int RedV;
	int GreenV;
	int BlueV;
    int HorizontalLeft;
    int HorizontalRight;
    int VerticalBottom;
    int VerticalTop;	
	Square(int GivenRedV, int GivenGreenV, int GivenBlueV, int GivenHorizontalLeft, int GivenHorizontalRight, int GivenVerticalBottom, int GivenVerticalTop)
	{
		RedV = GivenRedV;
		GreenV = GivenGreenV;
		BlueV = GivenBlueV;
		HorizontalLeft = GivenHorizontalLeft;
		HorizontalRight = GivenHorizontalRight;
		VerticalBottom = GivenVerticalBottom;
		VerticalTop = GivenVerticalTop;
	}
};

