#include "Actor.h"

namespace Cpain {
		
	void Actor::update(float deltaTime) {
		transform.position += velocity * deltaTime;
		velocity *= (1.0f / (1.0f + (damping * deltaTime)));
	}

	void Actor::draw(Renderer& renderer) {
		m_model->draw(renderer, transform);
	}

}
