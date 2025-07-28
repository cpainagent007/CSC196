#pragma once

#include "../Math/Transform.h"
#include "../Renderer/Model.h"
#include "Scene.h"

#include <memory>
#include <string>

namespace Cpain {
	class Actor {
	public:
		std::string name;
		std::string tag;

		vec2 velocity{ 0, 0 };
		float damping = 0.0f;		

		Transform transform;
		Scene* scene = nullptr;

	public:
		Actor() = default;
		Actor(const Transform& transform, std::shared_ptr<class Model> model)
			: transform{ transform }, m_model { model } {}

		virtual void update(float deltaTime);
		virtual void draw(class Renderer& renderer);

		Transform& getTransform() { return transform; }

	protected:
		std::shared_ptr<Model> m_model;
	};
}