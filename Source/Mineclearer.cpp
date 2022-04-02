#define OLC_PGE_APPLICATION
#include "Mineclearer.h"
#include "Config.h"

Mineclearer::Mineclearer() :
	grid(new Grid(*this, gameState)),
	footer(*this, gameState)
{
	sAppName = "Mineclearer";

	Construct(
		Config::screenResolution.x,
		Config::screenResolution.y,
		2,
		2,
		false,
		true
	);
	Start();
}

bool Mineclearer::OnUserCreate() {

	return true;
}

bool Mineclearer::OnUserUpdate(float deltaTime) {
	Clear(Config::theme.primary);

	if (gameState.playing) gameState.playTime += deltaTime;

	updateUI();
	footer.draw();
	grid->draw();

	return true;
}

void Mineclearer::updateUI() {
	if (gameState.state != State::DuringGame) {
		if (GetKey(olc::ENTER).bPressed || GetKey(olc::RETURN).bPressed) {
			delete grid;

			gameState.playTime = 0;
			gameState.state = State::DuringGame;

			grid = new Grid(*this, gameState);
		}
	}
}