#include "Bullet.h"

#include "Engine.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"

void Bullet::update(float deltaTime) {
	Cpain::vec2 inputDirection{ 1, 0 };


	Cpain::vec2 force = Cpain::vec2{ 1, 0 }.rotate(Cpain::degToRad(transform.rotation)) * speed;
	velocity += force;

	transform.position.x = Cpain::wrap(transform.position.x, 0.0f, (float)Cpain::getEngine().getRenderer().getWidth());
	transform.position.y = Cpain::wrap(transform.position.y, 0.0f, (float)Cpain::getEngine().getRenderer().getHeight());

	Actor::update(deltaTime);
}

void Bullet::onCollision(Actor* collider){
	if (tag != collider->tag) {
		active = false;
	}
}
