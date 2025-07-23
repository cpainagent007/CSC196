#pragma once

#include <vector>
#include <memory>
#include <string>

namespace Cpain {
	class Actor;
	class Scene {
	public:
		Scene() = default;

		void update(float deltaTime);
		void draw(class Renderer& renderer);
		void addActor(std::unique_ptr<class Actor>);

		Actor* getActorByName(const std::string& name);

	private:
		std::vector<std::unique_ptr<class Actor>> m_actors;

	};
}