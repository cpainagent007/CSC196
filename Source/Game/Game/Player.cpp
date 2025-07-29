#include "Player.h"
#include "Engine.h"
#include "Input/InputSystem.h"
#include "Math/Math.h"
#include "Renderer/Renderer.h"
#include "GameData.h"
#include "Bullet.h"
#include "Renderer/Model.h"
#include "Framework/Scene.h"

void Player::update(float deltaTime) {

	float rotate = 0;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_D)) rotate = +1;
	transform.rotation += (rotate * rotationSpeed) * deltaTime;

	float thrust = 0;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_W)) thrust = +1;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_S)) thrust = -1;

	Cpain::vec2 inputDirection{ 1, 0 };
	Cpain::vec2 force = inputDirection.rotate(Cpain::degToRad(transform.rotation)) * thrust * shipSpeed;
	velocity += force * deltaTime;

	transform.position.x = Cpain::wrap(transform.position.x, 0.0f, (float)Cpain::getEngine().getRenderer().getWidth());
	transform.position.y = Cpain::wrap(transform.position.y, 0.0f, (float)Cpain::getEngine().getRenderer().getHeight());

	fireTimer -= deltaTime;
	if (Cpain::getEngine().getInput().getKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0) {
		fireTimer = fireRate;

		std::shared_ptr<Cpain::Model> model = std::make_shared<Cpain::Model>(Cpain::bulletPoints, Cpain::vec3{ 1.0f, 1.0f, 0.0f });
		Cpain::Transform transform{ this->transform.position, this->transform.rotation, 5 };
		auto bullet = std::make_unique<Bullet>(transform, model);
		bullet->speed = 6.0f;
		bullet->lifespan = 0.35f;
		bullet->name = "bullet";
		bullet->tag = "player";

		scene->addActor(std::move(bullet));

	}

	Actor::update(deltaTime);

}

void Player::onCollision(Actor* collider){
	if (tag != collider->tag) {
		active = false;
	}
}
