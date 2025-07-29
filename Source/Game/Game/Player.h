#pragma once

#include "Framework/Actor.h"

class Player : public Cpain::Actor {
public:
	float shipSpeed = 200.0f;
	float rotationSpeed = 180.0f;
	float fireRate = 0.5f;
	float fireTimer = 0.0f;

public:
	Player() = default;
	Player(const Cpain::Transform& transform, std::shared_ptr<class Cpain::Model> model) :
		Cpain::Actor{ transform, model } {}

	void update(float deltaTime) override;

	void onCollision(Actor* collider) override;

};