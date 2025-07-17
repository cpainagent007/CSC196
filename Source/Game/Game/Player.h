#pragma once

#include "Game/Actor.h"

class Player : public Cpain::CActor::Actor {
public:
	Player() = default;
	Player(const Cpain::Transform& transform, std::shared_ptr<class Cpain::Model> model) :
		Actor{ transform, model } {}

	void update(float deltaTime) override;

private:

};