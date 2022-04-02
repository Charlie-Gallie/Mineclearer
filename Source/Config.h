#pragma once
#include "olcPixelGameEngine.h"

struct Theme {
	inline static olc::Pixel
		primary = olc::Pixel(20, 100, 155),
		secondary = olc::Pixel(255, 255, 255),
		tertiary = olc::Pixel(80, 100, 120),
		flagColor = olc::Pixel(0, 0, 30),
		mineColor = olc::Pixel(100, 20, 20),
		mineWinColor = olc::Pixel(80, 80, 80);
};

struct Config {
	inline static Theme theme = Theme{};
	inline static int gridSize = 15;

	inline static int footerDepth = 60;
	inline static olc::vi2d screenResolution = olc::vi2d(301, 301 + footerDepth);

	inline static olc::vi2d cellSize = {
		screenResolution.x / gridSize,
		(screenResolution.y - footerDepth) / gridSize
	};

	inline static olc::Pixel textColors[8] = {
		olc::Pixel(10, 180, 10),
		olc::Pixel(240, 180, 50),
		olc::Pixel(160, 50, 200),
		olc::Pixel(250, 90, 50),
		olc::Pixel(240, 255, 0),
		olc::Pixel(255, 0, 180),
		olc::Pixel(20, 40, 255),
		olc::Pixel(255, 255, 255),
	};

	inline static char
		mineSymbol = '*',
		flagSymbol = '!';

	inline static std::string
		winMessgae = "You win!",
		loseMessage = "You lose",
		playAgainMessage = "Press [ENTER] to play again";
};