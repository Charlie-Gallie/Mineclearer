#include "Cell.h"
#include "Config.h"

#include <random>

Cell::Cell(
	olc::PixelGameEngine& _PGE,
	GameState& _gameState,
	olc::vi2d _position,
	std::vector<std::vector<Cell*>>& _grid,
	olc::vi2d _positionInArray
) :
	PGE(_PGE),
	gameState(_gameState),
	position(_position),
	grid(_grid),
	positionInArray(_positionInArray)
{
	std::random_device randomDevice;
	std::mt19937 range(randomDevice());
	std::uniform_int_distribution<std::mt19937::result_type> distribution(1, Config::gridSize);

	if (distribution(range) > 13) {
		isMine = true;
		setCharacter(Config::mineSymbol);
	}

	characterSize = PGE.GetTextSize(std::string(1, character));
	flagSymbolSize = PGE.GetTextSize(std::string(1, Config::flagSymbol));
}

void Cell::draw() {
	// Left click
	if (gameState.state == State::DuringGame) {
		if (PGE.GetMouse(0).bPressed) {
			olc::vi2d mousePosition = PGE.GetMousePos();
			if (
				(mousePosition.x > position.x) && (mousePosition.x < position.x + Config::cellSize.x) &&
				(mousePosition.y > position.y) && (mousePosition.y < position.y + Config::cellSize.y)
				) {
				gameState.playing = true;
				setFlagged(false);
				setRevealed(true);
			}
		}
	}

	switch (gameState.state) {
	case State::WinGame: {
		if (isMine) characterColor = Config::theme.secondary;
		break;
	}
	}

	// Right click
	if (PGE.GetMouse(1).bPressed) {
		olc::vi2d mousePosition = PGE.GetMousePos();
		if (
			(mousePosition.x > position.x) && (mousePosition.x < position.x + Config::cellSize.x) &&
			(mousePosition.y > position.y) && (mousePosition.y < position.y + Config::cellSize.y)
		) {
			setFlagged(!flagged);
		}
	}

	// Outline
	PGE.DrawRect(
		{
			position.x + 1,
			position.y + 1
		},
		{
			Config::cellSize.x - 2,
			Config::cellSize.y - 2
		},
		Config::theme.secondary
	);

	// Fill color
	if (!revealed) {
		PGE.FillRect(
			{
				position.x + 2,
				position.y + 2
			},
			{
				Config::cellSize.x - 3,
				Config::cellSize.y - 3
			},
			Config::theme.tertiary
		);
	}

	// Character
	if (revealed) {
		PGE.DrawString(
			{
				(position.x + (Config::cellSize.x / 2) - characterSize.x / 2) - 3,
				(position.y + (Config::cellSize.y / 2) - characterSize.y / 2) - 3
			},
			std::string(1, character),
			characterColor,
			2
		);
	}

	// Flag
	if (flagged) {
		if (!revealed) {
			PGE.DrawString(
				{
					(position.x + (Config::cellSize.x / 2) - flagSymbolSize.x / 2) - 3,
					(position.y + (Config::cellSize.y / 2) - flagSymbolSize.y / 2) - 3
				},
				std::string(1, Config::flagSymbol),
				Config::theme.flagColor,
				2
			);
		}
	}

	if(gameState.state != State::DuringGame) setRevealed(true, true); // check for game complete
}

std::vector<olc::vi2d> Cell::getAdjacentCells() {
	std::vector<olc::vi2d> cells;

	for (int x = positionInArray.x - 1; x <= (positionInArray.x + 1); x++) {
		for (int y = positionInArray.y - 1; y <= (positionInArray.y + 1); y++) {
			if (
				(x >= 0) && (y >= 0) &&
				(x < Config::gridSize) && (y < Config::gridSize)
			) {
				olc::vi2d cell = { x, y };
				if(cell != positionInArray)
					cells.push_back(cell);
			}
		}
	}

	return cells;
}

void Cell::setCharacter(char _character) {
	character = _character;

	if (isdigit(character)) {
		int index = (character - '0');

		if(index > 0) characterColor = Config::textColors[index - 1];
		else character = ' ';
	}
	else characterColor = Config::theme.mineColor;
}

void Cell::clearArea() {
	if (!isMine) revealed = true;
	else return;

	if (character == ' ') {
		for (olc::vi2d cellPosition : getAdjacentCells()) {
			Cell* cell = grid[cellPosition.x][cellPosition.y];
			if (!cell->revealed && !cell->flagged)
				cell->setRevealed(true);
		}
	}
}

void Cell::loseGame() {
	setCharacter(Config::mineSymbol);
	gameState.playing = false;
	gameState.state = State::LoseGame;
}

void Cell::setFlagged(bool _flagged) {
	if (!revealed) {
		flagged = !flagged;
		gameState.flags += flagged ? 1 : -1;
	}
}

void Cell::setRevealed(bool _revealed, bool bypassLose) {
	if (isMine && !bypassLose) loseGame();
	if (!revealed && !isMine) {
		if (flagged) {
			flagged = false;
			gameState.flags -= 1;
		}

		int adjacentMines = 0;
		for (olc::vi2d cell : getAdjacentCells()) if (grid[cell.x][cell.y]->isMine) adjacentMines++;

		setCharacter('0' + adjacentMines);

		if (adjacentMines == 0) {
			clearArea();
		}
	}

	revealed = _revealed;
}