#include "Footer.h"
#include "Config.h"

#include <iostream>

Footer::Footer(
	olc::PixelGameEngine& _PGE,
	GameState& _gameState
) :
	PGE(_PGE),
	gameState(_gameState)
{
	position = {
		1,
		(Config::screenResolution.y - Config::footerDepth) + 1
	};

	winMessageSize = PGE.GetTextSize(Config::winMessgae) * 2,
	loseMessageSize = PGE.GetTextSize(Config::loseMessage) * 2,
	playAgainSize = PGE.GetTextSize(Config::playAgainMessage);
}

void Footer::drawPlayAgainMessage() {
	PGE.DrawString(
		{
			(Config::screenResolution.x / 2) - (playAgainSize.x / 2),
			(position.y + (Config::footerDepth / 2)) - (playAgainSize.y / 2) + 4
		},
		Config::playAgainMessage,
		Config::theme.secondary,
		1
	);
}

void Footer::drawPlayTime() {
	std::string timeMessage = "T: " + std::to_string((int)gameState.playTime);
	olc::vi2d timeSize = PGE.GetTextSize(timeMessage);

	PGE.DrawString(
		{
			(Config::screenResolution.x / 2) - (timeSize.x / 2),
			(position.y + (Config::footerDepth)) - (timeSize.y * 2)
		},
		timeMessage,
		Config::theme.secondary,
		1
	);
}

void Footer::draw() {
	PGE.DrawRect(
		position,
		{
			Config::screenResolution.x - 3,
			Config::footerDepth - 3
		},
		Config::theme.secondary
	);

	switch (gameState.state) {
	case State::DuringGame: {
		std::string
			minesLeft = std::string(1, Config::mineSymbol) + ": " + std::to_string(gameState.mines),
			flagsPlaced = std::string(1, Config::flagSymbol) + ": " + std::to_string(gameState.flags);
		olc::vi2d
			minesSize = PGE.GetTextSize(minesLeft),
			flagsSize = PGE.GetTextSize(flagsPlaced);

		PGE.DrawString(
			{
				(Config::screenResolution.x / 2) - (minesSize.x / 2),
				(position.y + (Config::footerDepth / 5)) - (minesSize.y / 2)
			},
			minesLeft,
			Config::theme.secondary,
			1
		);

		PGE.DrawString(
			{
				(Config::screenResolution.x / 2) - (flagsSize.x / 2),
				(position.y + (Config::footerDepth / 2)) - (flagsSize.y / 2)
			},
			flagsPlaced,
			Config::theme.secondary,
			1
		);
		drawPlayTime();

		break;
	}
	case State::WinGame: {
		PGE.DrawString(
			{
				(Config::screenResolution.x / 2) - (winMessageSize.x / 2),
				(position.y + (Config::footerDepth / 4)) - (winMessageSize.y / 2)
			},
			Config::winMessgae,
			Config::theme.secondary,
			2
		);
		drawPlayAgainMessage();
		drawPlayTime();

		break;
	}
	case State::LoseGame: {
		PGE.DrawString(
			{
				(Config::screenResolution.x / 2) - (loseMessageSize.x / 2),
				(position.y + (Config::footerDepth / 4)) - (loseMessageSize.y / 2)
			},
			Config::loseMessage,
			Config::theme.secondary,
			2
		);
		drawPlayAgainMessage();
		drawPlayTime();

		break;
	}
	}
}