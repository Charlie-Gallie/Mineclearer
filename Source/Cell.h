#pragma once
#include "olcPixelGameEngine.h"
#include "GameState.h"

class Cell {
public:
	Cell(olc::PixelGameEngine&, GameState&, olc::vi2d, std::vector<std::vector<Cell*>>&, olc::vi2d);

	olc::vi2d getPosition() { return position; }
	bool isAMine() { return isMine; }
	bool isRevealed() { return revealed; }

	void draw();
	void setRevealed(bool, bool = false);
	void clearArea();
	void setFlagged(bool);
private:
	GameState& gameState;

	olc::PixelGameEngine& PGE;
	olc::vi2d position;

	char
		character = ' ';

	olc::Pixel characterColor;
	olc::vi2d
		characterSize,
		flagSymbolSize;

	bool
		revealed = false,
		flagged = false,
		isMine = false;

	std::vector<olc::vi2d> getAdjacentCells();

	std::vector<std::vector<Cell*>>& grid;
	olc::vi2d positionInArray;

	void setCharacter(char);
	void loseGame();
};