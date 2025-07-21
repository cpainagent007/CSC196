#pragma once

#include "Framework/Actor.h"

class Enemy : public Cpain::CActor::Actor {
public:
	Enemy() = default;
	Enemy(const Cpain::Transform& transform, std::shared_ptr<class Cpain::Model> model) :
		Actor{ transform, model } {
	}

	void update(float deltaTime) override;

private:

};