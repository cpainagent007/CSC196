#include "Enemy.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"
#include "Framework/Game.h"
#include "Bullet.h"
#include "GameData.h" 
#include "Math/Vector3.h"
#include "Renderer/Model.h"

void Enemy::update(float deltaTime) {

	float speed = 100.0f;
	Cpain::vec2 inputDirection{ 1, 0 };

	Actor* player = scene->getActorByName("player");
	if (player) {
		inputDirection = player->transform.position - transform.position;
		inputDirection = inputDirection.normalized();
		transform.rotation = Cpain::radToDeg(inputDirection.angle());
	}

	Cpain::vec2 force = Cpain::vec2{ 1, 0 }.rotate(Cpain::degToRad(transform.rotation)) * speed;
	velocity += force * deltaTime;

	transform.position.x = Cpain::wrap(transform.position.x, 0.0f, (float)Cpain::getEngine().getRenderer().getWidth());
	transform.position.y = Cpain::wrap(transform.position.y, 0.0f, (float)Cpain::getEngine().getRenderer().getHeight());

	fireTimer -= deltaTime;
	if (fireTimer <= 0) {
		fireTimer = fireRate;

		std::shared_ptr<Cpain::Model> model = std::make_shared<Cpain::Model>(Cpain::bulletPoints, Cpain::vec3{ 1.0f, 0.0f, 0.0f });
		Cpain::Transform transform{ this->transform.position, this->transform.rotation, 5 };
		auto bullet = std::make_unique<Bullet>(transform, model);
		bullet->speed = 4.0f;
		bullet->lifespan = 0.35f;
		bullet->name = "bullet";
		bullet->tag = "enemy";

		scene->addActor(std::move(bullet));

	}

	Actor::update(deltaTime);
}

void Enemy::onCollision(Actor* collider){
	if (tag != collider->tag) {
		active = false;
		scene->getGame()->addPoints(10);
	}
}
