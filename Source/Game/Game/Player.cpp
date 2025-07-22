#include "Player.h"
#include "Engine.h"
#include "Input/InputSystem.h"

void Player::update(float deltaTime) {
	float shipSpeed = 200.0f;

	Cpain::vec2 inputDirection{ 0, 0 };

	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_S)) inputDirection.y = 1;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_D)) inputDirection.x = 1;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_W)) inputDirection.y = -1;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_A)) inputDirection.x = -1;

	if (inputDirection.lengthSqrd() > 0) {
		inputDirection = inputDirection.normalized();
		m_transform.position += (inputDirection * shipSpeed) * deltaTime;
	}
}