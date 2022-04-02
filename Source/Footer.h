#pragma once
#include "olcPixelGameEngine.h"
#include "GameState.h"

class Footer {
public:
	Footer(olc::PixelGameEngine&, GameState&);

	void draw();
private:
	olc::vi2d
		winMessageSize,
		loseMessageSize,
		playAgainSize;

	olc::PixelGameEngine& PGE;
	GameState& gameState;

	olc::vi2d position;

	void drawPlayAgainMessage();
	void drawPlayTime();
};