#pragma once

#include "Framework/Game.h"
#include "Framework/Scene.h"

class SpaceGame : public Cpain::Game {
public:
	SpaceGame() = default;

	bool initialize() override;
	void update() override;
	void shutdown() override;
	void draw() override;


private:
	std::unique_ptr<Cpain::Scene> m_scene;

};