#pragma once
#include "Framework/Game.h"

class SpaceGame : public Cpain::CGame::Game {
public:
	SpaceGame() = default;

	bool initialize() override;
	void update() override;
	void shutdown() override;
	void draw() override;


private:


};