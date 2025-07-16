#pragma once

#include "../Math/Transform.h"
#include "../Renderer/Model.h"

namespace Cpain {
	namespace CActor {
		class Actor {

		public:
			Actor() = default;
			Actor(const Transform& transform, class Model* model)
				: m_transform{ transform }, m_model { model } {}

			virtual void update(float deltaTime);
			virtual void draw(class Renderer& renderer);

			Transform& getTransform() { return m_transform; }

		protected:
			Transform m_transform;
			Model* m_model;

		};
	}
}