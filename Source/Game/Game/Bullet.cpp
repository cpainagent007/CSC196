#include "Bullet.h"

#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"

void Bullet::update(float deltaTime) {

	float speed = 100.0f;
	Cpain::vec2 inputDirection{ 1, 0 };


	Cpain::vec2 force = inputDirection.rotate(Cpain::degToRad(transform.rotation)) * speed;
	velocity += force * deltaTime;

	transform.position.x = Cpain::wrap(transform.position.x, 0.0f, (float)Cpain::getEngine().getRenderer().getWidth());
	transform.position.y = Cpain::wrap(transform.position.y, 0.0f, (float)Cpain::getEngine().getRenderer().getHeight());

	Actor::update(deltaTime);
}