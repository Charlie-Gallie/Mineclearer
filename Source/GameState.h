#pragma once

enum class State {
	DuringGame,
	WinGame,
	LoseGame
};

class GameState {
public:
	State state = State::DuringGame;
	bool playing = false;
	int
		mines,
		flags;
	float playTime;
};