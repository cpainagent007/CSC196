#pragma once

#include "Framework/Actor.h"

class Enemy : public Cpain::Actor {
public:
	Enemy() = default;
	Enemy(const Cpain::Transform& transform, std::shared_ptr<class Cpain::Model> model) :
		Cpain::Actor{ transform, model } {
	}

	void update(float deltaTime) override;

private:

};