#pragma once
#include <memory>

namespace Cpain {
	class Game {
	public:
		Game() = default;

		virtual bool initialize() = 0;
		virtual void update(float deltaTime) = 0;
		virtual void shutdown() = 0;
		virtual void draw() = 0;

	protected:
		std::unique_ptr<class Scene> m_scene;
		int m_score = 0;
		int m_lives = 0;

	};	
}