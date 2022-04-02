#include "Grid.h"

#include <iostream>

Grid::Grid(olc::PixelGameEngine& _PGE, GameState& _gameState) :
	PGE(_PGE),
	gameState(_gameState)
{
	gameState.mines = 0;
	gameState.flags = 0;

	// 2D vector initialisation
	grid = std::vector<std::vector<Cell*>>(Config::gridSize, std::vector<Cell*>(Config::gridSize, nullptr));

	for (int rows = 0; rows < Config::gridSize; rows++) {
		for (int columns = 0; columns < Config::gridSize; columns++) {
			grid[rows][columns] = new Cell(
				PGE,
				gameState,
				{
					(rows * Config::cellSize.x),
					(columns * Config::cellSize.y)
				},
				grid,
				{
					rows,
					columns
				}
			);
			if (grid[rows][columns]->isAMine()) gameState.mines++;
		}
	}
}

void Grid::draw() {
	int rev = 0;
	for (int rows = 0; rows < Config::gridSize; rows++) {
		for (int columns = 0; columns < Config::gridSize; columns++) {
			if (grid[rows][columns]->isRevealed()) rev++;
		}
	}
	if (rev == pow(Config::gridSize, 2) - gameState.mines) {
		gameState.state = State::WinGame;
		gameState.playing = false;
	}

	for (int rows = 0; rows < Config::gridSize; rows++) {
		for (int columns = 0; columns < Config::gridSize; columns++) {
			grid[rows][columns]->draw();
		}
	}
}