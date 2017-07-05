/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once
#include "ColorBox.h"
#include <vector>
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <time.h>
#include "Windows.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	int TLRed = 50;
	int TLGreen = 0;
	int TLBlue = 0;

	int TRRed = 0;
	int TRGreen = 0;
	int TRBlue = 50;

	int BLRed = 50;
	int BLGreen = 50;
	int BLBlue = 0;

	int BRRed = 0;
	int BRGreen = 50;
	int BRBlue = 0;

	std::vector<int> ColorPattern;
	std::vector<int> UserInput;
	bool IsComputerTurn;
	bool IsTitleScreen = false;
	int NextColor;
	int TimeOut;

	const int AxisX = 400;
	const int AxisY = 300;

	/********************************/
};