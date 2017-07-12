/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include <ctime>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	RedTopLeft(255, 0, 0, -100, -5, -5, -100),
	BlueTopRight(0, 0, 255, +5, +100, -5, -100),
	YellowBottomLeft(255, 255, 0, -100, -5, +100, +5),
	GreenBottomRight(0, 255, 0, +5, +100, +100, +5)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if(GameOver)
	{ // Title screen right here. Yeah, Im lazy
	}
	else
	{
		if (IsComputerTurn)
		{
			srand(time(NULL));
			if (IsColorAdded == false)
			{
				ColorPattern.push_back(rand() % 4 + 1);
				IsColorAdded = true;
			}
			if (TimeOutForSetColor == 0)
			{

				WhichColor(ColorPattern);
				TimeOutForSetColor = 60;
				IndexForColorPattern++;
				///Possibly problematic because it continues after last color that is shown, without waiting for 60 frames.
				if (IndexForColorPattern == ColorPattern.size() - 1)
				{
					IsComputerTurn = false;
					IsColorAdded = false;
					IndexForColorPattern = 0;
				}
			}
			RevertAllColorsToNormalSlowly(RedTopLeft, 1);
			RevertAllColorsToNormalSlowly(BlueTopRight, 2);
			RevertAllColorsToNormalSlowly(YellowBottomLeft, 3);
			RevertAllColorsToNormalSlowly(GreenBottomRight, 4);
			TimeOutForSetColor--;
		}
		else
		{
			if (UserInput.size() != ColorPattern.size())
			{
				if (wnd.mouse.GetPosX() > RedTopLeft.HorizontalLeft + AxisX && wnd.mouse.GetPosX() < AxisX && wnd.mouse.GetPosY() < AxisY && wnd.mouse.GetPosY() > AxisY + RedTopLeft.VerticalTop && wnd.mouse.LeftIsPressed() && TimeOutForSetColor == 0)
				{
					UserInput.push_back(1);
					SetColor(RedTopLeft, 30, 0, 0);
					TimeOutForSetColor = 30;
					if (UserInput[UserInput.size() - 1] != ColorPattern[UserInput.size() - 1])
					{
						GameOver = true;
					}
				}
				if (wnd.mouse.GetPosX() > AxisX && wnd.mouse.GetPosX() < AxisX + BlueTopRight.HorizontalRight && wnd.mouse.GetPosY() < AxisY && wnd.mouse.GetPosY() > AxisY + BlueTopRight.VerticalTop && wnd.mouse.LeftIsPressed() && TimeOutForSetColor == 0)
				{
					UserInput.push_back(2);
					SetColor(BlueTopRight, 0, 0, 30);
					TimeOutForSetColor = 30;
					if (UserInput[UserInput.size() - 1] != ColorPattern[UserInput.size() - 1])
					{
						GameOver = true;
					}
				}
				if (wnd.mouse.GetPosX() > YellowBottomLeft.HorizontalLeft + AxisX && wnd.mouse.GetPosX() < AxisX && wnd.mouse.GetPosY() > AxisY && wnd.mouse.GetPosY() < AxisY + YellowBottomLeft.VerticalBottom && wnd.mouse.LeftIsPressed() && TimeOutForSetColor == 0)
				{
					UserInput.push_back(3);
					SetColor(BlueTopRight, 30, 30, 0);
					TimeOutForSetColor = 30;
					if (UserInput[UserInput.size() - 1] != ColorPattern[UserInput.size() - 1])
					{
						GameOver = true;
					}
				}
				if (wnd.mouse.GetPosX() > AxisX && wnd.mouse.GetPosX() < AxisX + GreenBottomRight.HorizontalRight && wnd.mouse.GetPosY() > AxisY && wnd.mouse.GetPosY() < AxisY + GreenBottomRight.VerticalBottom && wnd.mouse.LeftIsPressed() && TimeOutForSetColor == 0)
				{
					UserInput.push_back(4);
					SetColor(BlueTopRight, 0, 30, 0);
					TimeOutForSetColor = 30;
					if (UserInput[UserInput.size() - 1] != ColorPattern[UserInput.size() - 1])
					{
						GameOver = true;
					}
				}
				TimeOutForSetColor--;
				RevertAllColorsToNormalSlowly(RedTopLeft, 1);
				RevertAllColorsToNormalSlowly(BlueTopRight, 2);
				RevertAllColorsToNormalSlowly(YellowBottomLeft, 3);
				RevertAllColorsToNormalSlowly(GreenBottomRight, 4);
			}
			else
			{
				IsComputerTurn = true;
			}

		}
	}
}

void Game::ComposeFrame()
{
	if (GameOver)
	{
	}
	else {
		for (int TempX = RedTopLeft.HorizontalLeft; TempX < RedTopLeft.HorizontalRight; TempX++)
		{
			for (int TempY = RedTopLeft.VerticalTop; TempY < RedTopLeft.VerticalBottom; TempY++)
				gfx.PutPixel(AxisX + TempX, AxisY + TempY, RedTopLeft.RedV, RedTopLeft.GreenV, RedTopLeft.BlueV);
		}
		for (int TempX = BlueTopRight.HorizontalLeft; TempX < BlueTopRight.HorizontalRight; TempX++)
		{
			for (int TempY = BlueTopRight.VerticalTop; TempY < BlueTopRight.VerticalBottom; TempY++)
				gfx.PutPixel(AxisX + TempX, AxisY + TempY, BlueTopRight.RedV, BlueTopRight.GreenV, BlueTopRight.BlueV);
		}
		for (int TempX = YellowBottomLeft.HorizontalLeft; TempX < YellowBottomLeft.HorizontalRight; TempX++)
		{
			for (int TempY = YellowBottomLeft.VerticalTop; TempY < YellowBottomLeft.VerticalBottom; TempY++)
				gfx.PutPixel(AxisX + TempX, AxisY + TempY, YellowBottomLeft.RedV, YellowBottomLeft.GreenV, YellowBottomLeft.BlueV);
		}
		for (int TempX = GreenBottomRight.HorizontalLeft; TempX < GreenBottomRight.HorizontalRight; TempX++)
		{
			for (int TempY = GreenBottomRight.VerticalTop; TempY < GreenBottomRight.VerticalBottom; TempY++)
				gfx.PutPixel(AxisX + TempX, AxisY + TempY, GreenBottomRight.RedV, GreenBottomRight.GreenV, GreenBottomRight.BlueV);
		}
	}
}

void Game::SetColor(Square& Gold, int GivenRedV, int GivenGreenV, int GivenBlueV)
{
	Gold.RedV = GivenRedV;
	Gold.GreenV = GivenGreenV;
	Gold.BlueV = GivenBlueV;
}

void Game::RevertAllColorsToNormalSlowly(Square& Gold, int WhichSquare)
{
	switch (WhichSquare)
	{
	case 1:
		if(Gold.RedV < 255)
		Gold.RedV++;
		break;
	case 2:
		if(Gold.BlueV < 255)
		Gold.BlueV++;
		break;
	case 3:
		if(Gold.RedV < 255)
			Gold.RedV++;
		if (Gold.GreenV < 255)
			Gold.GreenV++;
		break;
	case 4:
		if (Gold.GreenV < 255)
			Gold.GreenV++;
		break;
	}
}

void Game::WhichColor(std::vector<int> ColorPattern)
{
	switch (ColorPattern[IndexForColorPattern])
	{
		case 1:
			SetColor(RedTopLeft, 30, 0, 0);
			break;
		case 2:
			SetColor(BlueTopRight, 0, 0, 30);
			break;
		case 3:
			SetColor(YellowBottomLeft, 30, 30, 0);
			break;
		case 4:
			SetColor(GreenBottomRight, 0, 30, 0);
			break;
		default:
			InitiateEndOfWorld(420, 69); ///Am not taking responsibility

	}


		
}

void Game::InitiateEndOfWorld(int RIP, int RIP2)
{
	//Everyone is now ded
}