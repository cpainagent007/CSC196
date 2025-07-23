#include "Player.h"
#include "Engine.h"
#include "Input/InputSystem.h"
#include "Math/Math.h"
#include "Renderer/Renderer.h"

void Player::update(float deltaTime) {

	float rotate = 0;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_D)) rotate = +1;
	transform.rotation += (rotate * rotationSpeed) * deltaTime;

	float thrust = 0;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_W)) thrust = +1;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_S)) thrust = -1;

	Cpain::vec2 inputDirection{ 1, 0 };
	Cpain::vec2 force = inputDirection.rotate(Cpain::degToRad(transform.rotation)) * shipSpeed;
	velocity += force * deltaTime;

	transform.position.x = Cpain::wrap(transform.position.x, 0.0f, (float)Cpain::getEngine().getRenderer().getWidth());
	transform.position.y = Cpain::wrap(transform.position.y, 0.0f, (float)Cpain::getEngine().getRenderer().getHeight());

	Actor::update(deltaTime);

}