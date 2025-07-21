#pragma once

#include "Actor.h"

#include <vector>
#include <memory>

namespace Cpain {
	namespace CScene {
		class Scene {
		public:
			Scene() = default;

			void update(float deltaTime);
			void draw(class Renderer& renderer);
			void addActor(std::unique_ptr<class Cpain::CActor::Actor>);

		private:
			std::vector<std::unique_ptr<class Cpain::CActor::Actor>> m_actors;

		};
	}
}