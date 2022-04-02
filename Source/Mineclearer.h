#pragma once
#include "olcPixelGameEngine.h"
#include "Grid.h"
#include "GameState.h"
#include "Footer.h"

class Mineclearer : public olc::PixelGameEngine {
public:
	Mineclearer();
	bool OnUserCreate();
	bool OnUserUpdate(float);
private:
	GameState& gameState = *(new GameState());
	Grid* grid;
	Footer footer;

	int
		mines,
		flags;

	void updateUI();
};