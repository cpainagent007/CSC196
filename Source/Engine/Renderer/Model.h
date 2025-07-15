#pragma once

#include "../Math/Vector2.h"
#include "../Math/Vector3.h"

#include <vector>

namespace Cpain {
	class Model {

	public:
		Model() = default;
		Model(const std::vector<Cpain::CVec2::vec2>& points, const Cpain::CVec3::vec3& color = { 1, 1, 1 })
			: m_points{ points }, m_color{ color } {
		}

		void draw(class Renderer& renderer, const Cpain::CVec2::vec2& position, float rotation, float scale);

	private:
		std::vector<Cpain::CVec2::vec2> m_points;
		Cpain::CVec3::vec3 m_color{ 1, 1, 1 };
	};
}