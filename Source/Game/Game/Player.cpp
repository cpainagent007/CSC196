#include "Player.h"
#include "Engine.h"
#include "Input/InputSystem.h"
#include "Math/Math.h"

void Player::update(float deltaTime) {

	float shipSpeed = 200.0f;
	float rotationSpeed = 10.0f;

	float rotate = 0;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_D)) rotate = +1;
	m_transform.rotation += (rotate * rotationSpeed) * deltaTime;

	float thrust = 0;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_W)) thrust = 1;

	Cpain::vec2 inputDirection{ 1, 0 };
	Cpain::vec2 force = inputDirection.rotate(Cpain::degToRad(m_transform.rotation)) * shipSpeed;
	velocity += force * deltaTime;

	Actor::update(deltaTime);

}