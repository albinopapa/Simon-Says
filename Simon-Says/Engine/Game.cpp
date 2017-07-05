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
#include <iostream>
#include <chrono>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	srand(time(NULL));
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
	if(IsTitleScreen)
	{ 
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			IsTitleScreen = false;
		}
	}
	else
	{
		if (IsComputerTurn)
		{
			//Add new pattern
			ColorPattern.push_back(rand() % 4 + 1);
			//Play the colors
			for (int i = 0; i < ColorPattern.size(); i++)
			{
				//Stuff for time, not very important.
				std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
				std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
				std::chrono::duration<float> runtime = end - start;
				float duration = runtime.count();
				switch (ColorPattern[i])
				{
				case 1:
					BLRed = 255;
					BLGreen = 255;
					BLBlue = 0;
					break;
				case 2:
					BRRed = 0;
					BRGreen = 255;
					BRBlue = 0;
					break;
				case 3:
					TRRed = 0;
					TRGreen = 0;
					TRBlue = 255;
					break;
				case 4:
					TLRed = 255;
					TLGreen = 0;
					TLBlue = 0;
					break;
				 }
				while (duration < 1)
				{
					end = std::chrono::steady_clock::now();
					runtime = end - start;
					duration = runtime.count();
					gfx.BeginFrame();
					ComposeFrame();
					gfx.EndFrame();
				}
				BLRed = 50;
				BLGreen = 50;
				BRGreen = 50;
				TRBlue = 50;
				TLRed = 50;
			}
			IsComputerTurn = false;
		}
		else
		{
			for (int i = 0; i < ColorPattern.size(); i++ )
			{
				std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
				std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
				std::chrono::duration<float> runtime = end - start;
				float duration = runtime.count();
				//Take input, then light up that color for a second
				while ((i + 1)!= UserInput.size())
				{
					//Which color has the user selected?
					if (wnd.mouse.LeftIsPressed() &&
						wnd.mouse.GetPosX() < AxisX &&
						wnd.mouse.GetPosX() > AxisX - 100 &&
						wnd.mouse.GetPosY() > AxisY &&
						wnd.mouse.GetPosY() < AxisY + 100)
					{
						UserInput.push_back(1);
						while (duration < 1)
						{
							BLRed = 255;
							BLGreen = 255;
							BLBlue = 0;
							end = std::chrono::steady_clock::now();
							runtime = end - start;
							duration = runtime.count();
							gfx.BeginFrame();
							ComposeFrame();
							gfx.EndFrame();
						}
						BLRed = 50;
						BLGreen = 50;
						BLBlue = 0;
					}else
					if (wnd.mouse.LeftIsPressed() &&
						wnd.mouse.GetPosX() > AxisX &&
						wnd.mouse.GetPosX() < AxisX + 100 &&
						wnd.mouse.GetPosY() > AxisY &&
						wnd.mouse.GetPosY() < AxisY + 100)
					{
						UserInput.push_back(2);
						while (duration < 1)
						{
							BRRed = 0;
							BRGreen = 255;
							BRBlue = 0;
							end = std::chrono::steady_clock::now();
							runtime = std::chrono::steady_clock::now() - start;
							duration = runtime.count();
							gfx.BeginFrame();
							ComposeFrame();
							gfx.EndFrame();
						}
						BRRed = 0;
						BRGreen = 50;
						BRBlue = 0;
					}else
					if (wnd.mouse.LeftIsPressed() &&
						wnd.mouse.GetPosX() < AxisX &&
						wnd.mouse.GetPosX() > AxisX - 100 &&
						wnd.mouse.GetPosY() < AxisY &&
						wnd.mouse.GetPosY() > AxisY - 100)
					{
						UserInput.push_back(4);

						while (duration < 1)
						{
							TLRed = 255;
							TLGreen = 0;
							TLBlue = 0;
							end = std::chrono::steady_clock::now();
							runtime = std::chrono::steady_clock::now() - start;
							duration = runtime.count();
							gfx.BeginFrame();
							ComposeFrame();
							gfx.EndFrame();
						}
						TLRed = 50;
						TLGreen = 0;
						TLBlue = 0;
					}else
					if (wnd.mouse.LeftIsPressed() &&
						wnd.mouse.GetPosX() > AxisX &&
						wnd.mouse.GetPosX() < AxisX + 100 &&
						wnd.mouse.GetPosY() < AxisY &&
						wnd.mouse.GetPosY() > AxisY - 100)
					{
						UserInput.push_back(3);
						while (duration < 1)
						{
							TRRed = 0;
							TRGreen = 0;
							TRBlue = 255;
							end = std::chrono::steady_clock::now();
							runtime = std::chrono::steady_clock::now() - start;
							duration = runtime.count();
							gfx.BeginFrame();
							ComposeFrame();
							gfx.EndFrame();
						}
						TRRed = 0;
						TRGreen = 0;
						TRBlue = 50;
					}
					//Did the User make a mistake?
				}
					if (ColorPattern[i] != UserInput[i])
					{
						i = ColorPattern.size() + 1;
						IsTitleScreen = true;
					}
			}
			IsComputerTurn = true;
			UserInput.clear();
		}
	}
}

void Game::ComposeFrame()
{
	int AxisX = 400;
	int AxisY = 300;
	for (int TempX = -100; TempX < -5; TempX++)
	{
		for (int TempY = -100; TempY < -5; TempY++)
		gfx.PutPixel(AxisX + TempX, AxisY + TempY, TLRed, TLGreen, TLBlue);
	}
	for (int TempX = 5; TempX < 100; TempX++)
	{
		for (int TempY = -5; TempY > -100; TempY--)
			gfx.PutPixel(AxisX + TempX, AxisY + TempY, TRRed, TRGreen, TRBlue);
	}
	for (int TempX = -100; TempX < -5; TempX++)
	{
		for (int TempY = 5; TempY < 100; TempY++)
			gfx.PutPixel(AxisX + TempX, AxisY + TempY, BLRed, BLGreen, BLBlue);
	}
	for (int TempX = 5; TempX < 100; TempX++)
	{
		for (int TempY = 5; TempY < 100; TempY++)
			gfx.PutPixel(AxisX + TempX, AxisY + TempY, BRRed, BRGreen, BRBlue);
	}


}


