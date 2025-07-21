#pragma once
#include <memory>

namespace Cpain {
	namespace CGame {
		class Game {
		public:
			Game() = default;

			virtual bool initialize() = 0;
			virtual void update() = 0;
			virtual void shutdown() = 0;
			virtual void draw() = 0;

		private:
			std::unique_ptr<class Scene> m_scene;

		};
	}	
}