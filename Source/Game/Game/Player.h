#pragma once

#include "Framework/Actor.h"

class Player : public Cpain::Actor {
public:
	Player() = default;
	Player(const Cpain::Transform& transform, std::shared_ptr<class Cpain::Model> model) :
		Cpain::Actor{ transform, model } {}

	void update(float deltaTime) override;

private:

};