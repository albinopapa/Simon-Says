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


/*
RedTopLeft(255, 0, 0, -100, -5, -5, -100),
BlueTopRight(0, 0, 255, +5, +100, -5, -100),
YellowBottomLeft(255, 255, 0, -100, -5, +100, +5),
GreenBottomRight(0, 255, 0, +5, +100, +100, +5)

*/
Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	RedTopLeft( 30, 0, 0, 255, 0, 0, AxisX + -100, AxisY + -100, AxisX + -5, AxisY + -5 ),
	BlueTopRight( 0, 0, 30, 0, 0, 255, AxisX + 5, AxisY + -100, AxisX + 100, AxisY + -5 ),
	YellowBottomLeft( 30, 30, 0, 255, 255, 0, AxisX + -100, AxisY + 5, AxisX + -5, AxisY + 100 ),
	GreenBottomRight( 0, 30, 0, 0, 255, 0, AxisX + 5, AxisY + 5, AxisX + 100, AxisY + 100 )
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
	if( GameOver )
	{ // Title screen right here. Yeah, Im lazy
	}
	else
	{
		if( IsComputerTurn )
		{
			if( IsColorAdded == false )
			{
				srand( time( NULL ) );
				ColorPattern.push_back( rand() % 4 + 1 );
				IsColorAdded = true;
			}
			if( TimeOutForSetColor == 0 )
			{

				WhichColor( ColorPattern );
				TimeOutForSetColor = 60;
				IndexForColorPattern++;
				if( IndexForColorPattern == ColorPattern.size() )
				{
					IsComputerTurn = false;
					IsColorAdded = false;
					IndexForColorPattern = 0;
				}
			}
			RevertAllColorsToNormalSlowly( RedTopLeft, 1 );
			RevertAllColorsToNormalSlowly( BlueTopRight, 2 );
			RevertAllColorsToNormalSlowly( YellowBottomLeft, 3 );
			RevertAllColorsToNormalSlowly( GreenBottomRight, 4 );
			if( TimeOutForSetColor != 0 ) { TimeOutForSetColor--; }
		}
		else
		{
			if( UserInput.size() != ColorPattern.size() )
			{
				auto HandleUserInput = [ this ]( int TileIdx, Square &Tile )
				{
					if( Tile.MouseOver( wnd.mouse.GetPosX(), wnd.mouse.GetPosY() ) &&
						wnd.mouse.LeftIsPressed() && TimeOutForSetColor == 0 )
					{
						UserInput.push_back( TileIdx );
						Tile.ResetColor();
						TimeOutForSetColor = 30;

						const auto inputIdx = UserInput.size() - 1;
						if( UserInput[ inputIdx ] != ColorPattern[ inputIdx ] )
						{
							GameOver = true;
						}
					}
				};
				HandleUserInput(1, RedTopLeft );
				HandleUserInput(2, BlueTopRight );
				HandleUserInput(3, YellowBottomLeft );
				HandleUserInput(4, GreenBottomRight );
				
				if( TimeOutForSetColor != 0 ) TimeOutForSetColor--;
				RevertAllColorsToNormalSlowly( RedTopLeft, 1 );
				RevertAllColorsToNormalSlowly( BlueTopRight, 2 );
				RevertAllColorsToNormalSlowly( YellowBottomLeft, 3 );
				RevertAllColorsToNormalSlowly( GreenBottomRight, 4 );
			}
			else
			{
				IsComputerTurn = true;
				UserInput.clear();
			}

		}
	}
}

void Game::ComposeFrame()
{
	if( GameOver )
	{
		//Try again next time
	}
	else
	{
		RedTopLeft.Draw( gfx );
		BlueTopRight.Draw( gfx );
		YellowBottomLeft.Draw( gfx );
		GreenBottomRight.Draw( gfx );
	}
}

void Game::SetColor( Square& Gold, int GivenRedV, int GivenGreenV, int GivenBlueV )
{
	Gold.red = GivenRedV;
	Gold.green = GivenGreenV;
	Gold.blue = GivenBlueV;
}

void Game::RevertAllColorsToNormalSlowly( Square& Tile, int WhichSquare )
{
	switch( WhichSquare )
	{
		case 1:
			if( Tile.red < Tile.maxRed ) Tile.red++;
			break;
		case 2:
			if( Tile.blue < Tile.maxBlue ) Tile.blue++;
			break;
		case 3:
			if( Tile.red < Tile.maxRed ) Tile.red++;
			if( Tile.green < Tile.maxGreen ) Tile.green++;
			break;
		case 4:
			if( Tile.green < Tile.maxGreen ) Tile.green++;
			break;
	}
}

void Game::WhichColor( std::vector<int> ColorPattern )
{
	switch( ColorPattern[ IndexForColorPattern ] )
	{
		case 1:
			SetColor( RedTopLeft, 30, 0, 0 );
			break;
		case 2:
			SetColor( BlueTopRight, 0, 0, 30 );
			break;
		case 3:
			SetColor( YellowBottomLeft, 30, 30, 0 );
			break;
		case 4:
			SetColor( GreenBottomRight, 0, 30, 0 );
			break;
		default:
			InitiateEndOfWorld( 420, 69 ); //Am not taking responsibility
	}
}

void Game::InitiateEndOfWorld( int RIP, int RIP2 )
{
	//Everyone is now ded
}