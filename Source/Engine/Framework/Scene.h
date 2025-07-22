#pragma once

#include "Actor.h"

#include <vector>
#include <memory>

namespace Cpain {
	class Scene {
	public:
		Scene() = default;

		void update(float deltaTime);
		void draw(class Renderer& renderer);
		void addActor(std::unique_ptr<class Actor>);

	private:
		std::vector<std::unique_ptr<class Actor>> m_actors;

	};
}