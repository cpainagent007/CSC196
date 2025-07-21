#include "Actor.h"

namespace Cpain {
	namespace CActor {
		
		void Actor::update(float deltaTime) {
			
		}

		void Actor::draw(Renderer& renderer) {
			m_model->draw(renderer, m_transform);
		}

	}
}
