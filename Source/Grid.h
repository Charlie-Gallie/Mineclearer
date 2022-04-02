#pragma once

#include <vector>
#include "olcPixelGameEngine.h"
#include "Cell.h"
#include "Config.h"
#include "GameState.h"

class Grid {
public:
	Grid(olc::PixelGameEngine&, GameState&);

	void draw();
private:
	GameState& gameState;
	std::vector<std::vector<Cell*>> grid;
	olc::PixelGameEngine& PGE;
};